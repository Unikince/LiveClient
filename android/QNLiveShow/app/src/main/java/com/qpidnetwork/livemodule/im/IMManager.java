package com.qpidnetwork.livemodule.im;

import android.content.Context;
import android.os.Handler;
import android.os.Message;
import android.text.TextUtils;

import com.qpidnetwork.livemodule.httprequest.item.GiftItem;
import com.qpidnetwork.livemodule.httprequest.item.LoginItem;
import com.qpidnetwork.livemodule.im.listener.IMClientListener;
import com.qpidnetwork.livemodule.im.listener.IMGiftMessageContent;
import com.qpidnetwork.livemodule.im.listener.IMMessageItem;
import com.qpidnetwork.livemodule.im.listener.IMRebateItem;
import com.qpidnetwork.livemodule.im.listener.IMRoomInItem;
import com.qpidnetwork.livemodule.im.listener.IMTextMessageContent;
import com.qpidnetwork.livemodule.im.listener.IMUserBaseInfoItem;
import com.qpidnetwork.livemodule.liveshow.authorization.IAuthorizationListener;
import com.qpidnetwork.livemodule.liveshow.liveroom.gift.GiftSender;
import com.qpidnetwork.livemodule.liveshow.model.http.HttpRespObject;
import com.qpidnetwork.livemodule.utils.Log;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.concurrent.atomic.AtomicInteger;

/**
 * IM聊天管理器（自动登录，事件分发等）
 * @author Hunter Mun
 * @since 2017-6-1
 */
public class IMManager extends IMClientListener implements IAuthorizationListener {
	
	private static final String TAG = IMManager.class.getName();
	public static final int IM_INVALID_REQID = -1;
	
	private Context mContext;
	private static IMManager mIMManager;
	private List<String> mUrlList;//IM连接Url
	
	/**
	 * Handler
	 */
	private Handler mHandler = null;
	
	/*登录相关*/
	private boolean mIsLogin = false; //是否已登录的标志
	private LoginItem mLoginItem; 	  //记录用户登录的个人信息
	private boolean mIsAutoRelogin = false; //是否自动重登录
	private final int mAutoReloginTime = 30 * 1000;	//自动登录间隔时长30秒

	/*基础管理类*/
	private IMUserBaseInfoManager mIMUserBaseInfoManager;

    /**
     * 礼物本地配置列表
     */
    private IMGiftManager mIMGiftManager;
	/**
	 * 消息ID生成器
	 */
	private AtomicInteger mMsgIdIndex = null;
	private static final int MsgIdIndexBegin = 1;
	private HashMap<Integer, IMMessageItem> mSendingMsgMap;  //记录发送中消息Map
	
	private IMEventListenerManager mListenerManager; //通知事件分发器

	private boolean isFirstSendLike = true; //在当前房间是否第一次发送点赞

	/**
	 * 请求操作类型
	 */
	private enum IMNotifyOptType {
		HttpLoginEvent,			//php登录通知
		HttpLogoutEvent,		//php注销通知
		IMLoginEvent,			//IM登录成功通知
		IMLogoutEvent,			//IM注销通知
		IMAutoLoginEvent		//IM自动登录事件
	}
	
	public static IMManager newInstance(Context context){
		if(mIMManager == null){
			mIMManager = new IMManager(context);
		}
		return mIMManager;
	}
	
	public static IMManager getInstance(){
		return mIMManager;
	}
	
	private IMManager(Context context){
		this.mContext = context;
		mUrlList = new ArrayList<String>();
		mUrlList.add("ws://172.25.32.17:3006");
		mIsLogin = false;
		mIsAutoRelogin = false;
		mListenerManager = new IMEventListenerManager();
		mMsgIdIndex = new AtomicInteger(MsgIdIndexBegin);
		mSendingMsgMap = new HashMap<Integer, IMMessageItem>();
		mIMUserBaseInfoManager = new IMUserBaseInfoManager();
        mIMGiftManager = IMGiftManager.getInstance();
		mHandler = new Handler(){
			@Override
			public void handleMessage(Message msg) {
				// TODO Auto-generated method stub
				super.handleMessage(msg);
				switch (IMNotifyOptType.values()[msg.what]) {
				case HttpLoginEvent:{
					HttpRespObject resp = (HttpRespObject)msg.obj;
					LoginItem item = (LoginItem)resp.data;
					if(resp.isSuccess && item != null){
						if(init()){
							//初始化成功,先注销
							Logout();
							Login(item);
						}else{
							Log.d(TAG, "IMManager::IMClient() init failed, urlListSize: " + mUrlList.size());
						}
					}else{
						if(mIsLogin){
							Logout();
						}
					}
				}break;

				case HttpLogoutEvent:{
					//php注销
					Logout();
				}break;
				
				case IMLoginEvent:{
					LCC_ERR_TYPE errType = LCC_ERR_TYPE.values()[msg.arg1];
					if(errType == LCC_ERR_TYPE.LCC_ERR_SUCCESS){
						mIsLogin = true;
					}else if(IsAutoRelogin(errType)){
						timerToAutoLogin();
					}else{
//						mLoginItem = null;
					}
				}break;
				
				case IMLogoutEvent:{
					LCC_ERR_TYPE errType = LCC_ERR_TYPE.values()[msg.arg1];
					mIsLogin = false;
					if(IsAutoRelogin(errType)){
						//断线，需要重连
						GiftSender.getInstance().imReconnecting = true;
						Log.d(TAG,"IMLogoutEvent-断线，需要重连");
						timerToAutoLogin();
					}else{
						//注销，清除本地缓存
						ResetParam();
					}
				}break;
				
				case IMAutoLoginEvent:{
					AutoRelogin();
				}break;
				
				default:
					break;
				}
			}
		};
	}

	/**
	 * 注册邀请启动监听器
	 * @param listener
	 * @return
	 */
	public boolean registerIMInviteLaunchEventListener(IMInviteLaunchEventListener listener){
		return mListenerManager.registerIMInviteLaunchEventListener(listener);
	}

	/**
	 * 注销邀请启动监听器
	 * @param listener
	 * @return
	 */
	public boolean unregisterIMInviteLaunchEventListener(IMInviteLaunchEventListener listener){
		return mListenerManager.unregisterIMInviteLaunchEventListener(listener);
	}

	/**
	 * 注册邀请启动监听器
	 * @param listener
	 * @return
	 */
	public boolean registerIMLiveRoomEventListener(IMLiveRoomEventListener listener){
		return mListenerManager.registerIMLiveRoomEventListener(listener);
	}

	/**
	 * 注销邀请启动监听器
	 * @param listener
	 * @return
	 */
	public boolean unregisterIMLiveRoomEventListener(IMLiveRoomEventListener listener){
		return mListenerManager.unregisterIMLiveRoomEventListener(listener);
	}

	/**
	 * 注册邀请启动监听器
	 * @param listener
	 * @return
	 */
	public boolean registerIMOtherEventListener(IMOtherEventListener listener){
		return mListenerManager.registerIMOtherEventListener(listener);
	}

	/**
	 * 注销邀请启动监听器
	 * @param listener
	 * @return
	 */
	public boolean unregisterIMOtherEventListener(IMOtherEventListener listener){
		return mListenerManager.unregisterIMOtherEventListener(listener);
	}
	
	/**
	 * 初始化Client及相关
	 * @return
	 */
	private boolean init(){
		boolean result = false;
		if(!mUrlList.isEmpty()){
			String[] urlArray = new String[mUrlList.size()];
			result = IMClient.init(mUrlList.toArray(urlArray), this);
		}
		return result;
	}
	
	/**
	 * 登录
	 * @param loginItem
	 * @return
	 */
	public synchronized boolean Login(LoginItem loginItem) {
		Log.d(TAG, "IMManager::Login() begin, userId:%s, mIsLogin:%b", loginItem.userId, mIsLogin);
		
		boolean result = false;
		if (mIsLogin) {
			result = mIsLogin;
		}else {
			if (!mIsAutoRelogin) {
				// 重置参数
				ResetParam();
			}
			// LiveChat登录
			result = IMClient.Login(loginItem.userId, loginItem.token);
			if (result){
				mIsAutoRelogin = true;
				if(GiftSender.getInstance().imReconnecting){
					GiftSender.getInstance().hasIMReconnected = true;
				}
				GiftSender.getInstance().imReconnecting = false;
				Log.d(TAG,"Login-断线重连成功");
				mLoginItem = loginItem;
			}
		}
		
		Log.d("LiveChatManager", "LiveChatManager::Login() end, userId:%s, result:%s", mLoginItem.userId, Boolean.toString(result));
		return result;
	}
	
	/**
	 * 定时执行自动登录
	 */
	private void timerToAutoLogin(){
		Message msg = Message.obtain();
		msg.what = IMNotifyOptType.IMAutoLoginEvent.ordinal();
		mHandler.sendMessageDelayed(msg, mAutoReloginTime);
	}
	
	/**
	 * 自动重登录
	 */
	private void AutoRelogin(){
		Log.d(TAG, "IMManager::AutoRelogin() begin, mUserId:%s, Token:%s", mLoginItem.userId, mLoginItem.token);
		
		if (!TextUtils.isEmpty(mLoginItem.userId) && !TextUtils.isEmpty(mLoginItem.token)){
			Login(mLoginItem);
		}
		
		Log.d(TAG, "IMManager::AutoRelogin() end");
	}
	
	/**
	 * 注销
	 * @return
	 */
	private synchronized boolean Logout() {
		Log.d(TAG, "IMManager::Logout() begin");
		// 设置不自动重登录
		mIsAutoRelogin = false;
		//更新点赞状态
		isFirstSendLike = true;

		boolean result =  IMClient.Logout();
		Log.d(TAG, "IMManager::Logout() end, result:%b", result);	
		
		return result;
	}
	
	/**
	 * 重置参数（用于注销后或登录前）
	 */
	private void ResetParam(){
//		mLoginItem = null;		//IM登录异常导致数据被清除后又未提出应用，发消息构建消息空指针异常，修改为PHP控制IM消息
		mMsgIdIndex.set(MsgIdIndexBegin);
	}
	
	/**
	 * 是否自动重登录
	 * @return
	 */
	private boolean IsAutoRelogin(LCC_ERR_TYPE errType)
	{
		if (mIsAutoRelogin)
		{
			mIsAutoRelogin = (errType == LCC_ERR_TYPE.LCC_ERR_CONNECTFAIL);
		}
		return mIsAutoRelogin;
	}

	/**
	 * 获取基础用户信息
	 * @param userId
	 * @return
	 */
	public IMUserBaseInfoItem getUserInfo(String userId){
		return mIMUserBaseInfoManager.getUserBaseInfo(userId);
	}

	/***************************** IM Client 功能接口   ********************************************/
	/**
	 * 成功返回有效的ReqId,否则不成功，无回调
	 * @param roomId
	 * @return
	 */
	public int RoomIn(String roomId){
		int reqId = IM_INVALID_REQID;
		//进入房间更新点赞状态
		isFirstSendLike = true;
		if(mIsLogin){
			reqId = IMClient.GetReqId();
			if(!IMClient.RoomIn(reqId, roomId)){
				reqId = IM_INVALID_REQID;
			}
		}
		return reqId;
	}
	
	/**
	 * 观众离开直播室
	 * @param roomId
	 * @return
	 */
	public int RoomOut(String roomId){
		int reqId = IM_INVALID_REQID;
		if(mIsLogin){
			reqId = IMClient.GetReqId();
			if(!IMClient.RoomOut(reqId, roomId)){
				reqId = IM_INVALID_REQID;
			}
		}
		return reqId;
	}

	/**
	 * 发送消息
	 * @param roomId
	 * @param msg
	 * @param targetIds
	 * @return
	 */
	public IMMessageItem sendRoomMsg(String roomId, String msg, String[] targetIds){
		int reqId = IMClient.GetReqId();
		IMMessageItem msgItem = new IMMessageItem(roomId, mMsgIdIndex.getAndIncrement(), mLoginItem.userId, mLoginItem.nickName,
				mLoginItem.level, IMMessageItem.MessageType.Normal, new IMTextMessageContent(msg), null);
		if(!mIsLogin || !IMClient.SendRoomMsg(reqId, roomId, mLoginItem.nickName, msg, targetIds)){
			return null;
		}else{
			//存储发送中消息
			mSendingMsgMap.put(Integer.valueOf(reqId), msgItem);
		}
		return msgItem;
	}

	/**
	 * 发送礼物(大小礼物)
	 * @param roomId
	 * @param giftItem
	 * @param count
	 * @param isMultiClick
	 * @param multiStart
	 * @param multiEnd
	 * @param multiClickId
	 * @return
	 */
	public IMMessageItem sendGift(String roomId, GiftItem giftItem, int count, boolean isMultiClick, int multiStart, int multiEnd, int multiClickId){
		int reqId = IMClient.GetReqId();
		IMGiftMessageContent msgContent = new IMGiftMessageContent(giftItem.id, giftItem.name, count, isMultiClick, multiStart, multiEnd, multiClickId);
		IMMessageItem msgItem = new IMMessageItem(roomId, mMsgIdIndex.getAndIncrement(), mLoginItem.userId, mLoginItem.nickName,
				mLoginItem.level, IMMessageItem.MessageType.Gift, null, msgContent);
		if(!mIsLogin || !IMClient.SendGift(reqId, roomId, mLoginItem.nickName, giftItem.id, giftItem.name, count, isMultiClick, multiStart, multiEnd, multiClickId)){
			return null;
		}else{
			//存储发送中消息
			mSendingMsgMap.put(Integer.valueOf(reqId), msgItem);
		}
		return msgItem;
	}

	/**
	 * 发送弹幕消息
	 * @param roomId
	 * @param message
	 * @return
	 */
	public IMMessageItem sendBarrage(String roomId, String message){
		int reqId = IMClient.GetReqId();
		IMMessageItem msgItem = new IMMessageItem(roomId, mMsgIdIndex.getAndIncrement(), mLoginItem.userId, mLoginItem.nickName,
				mLoginItem.level, IMMessageItem.MessageType.Barrage, new IMTextMessageContent(message), null);
		if(!mIsLogin || !IMClient.SendBarrage(reqId, roomId, mLoginItem.nickName, message)){
			return null;
		}else{
			//存储发送中消息
			mSendingMsgMap.put(Integer.valueOf(reqId), msgItem);
		}
		return msgItem;
	}

	/**
	 * 7.1.观众立即私密邀请
	 * @param userId
	 * @param isInitiative	主动发起/收到主播端通知后发起
	 * @return
	 */
	public int sendImmediatePrivateInvite(String userId, boolean isInitiative){
		int reqId = IM_INVALID_REQID;
		if(mIsLogin){
			reqId = IMClient.GetReqId();
			if(!IMClient.SendImmediatePrivateInvite(reqId, userId, isInitiative)){
				reqId = IM_INVALID_REQID;
			}
		}
		return reqId;
	}

	/**
	 * 7.2.观众取消立即私密邀请
	 * @param inviteId
	 * @return
	 */
	public int cancelImmediatePrivateInvite(String inviteId){
		int reqId = IM_INVALID_REQID;
		if(mIsLogin){
			reqId = IMClient.GetReqId();
			if(!IMClient.CancelImmediatePrivateInvite(reqId, inviteId)){
				reqId = IM_INVALID_REQID;
			}
		}
		return reqId;
	}
	
	/**************************** Authorization Listener  **************************************/
	@Override
	public void onLogin(boolean isSuccess, int errCode, String errMsg,
			LoginItem item) {
		Message msg = Message.obtain();
		msg.what = IMNotifyOptType.HttpLoginEvent.ordinal();
		msg.obj = new HttpRespObject(isSuccess, errCode, errMsg, item);
		mHandler.sendMessage(msg);
	}

	@Override
	public void onLogout() {
		Message msg = Message.obtain();
		msg.what = IMNotifyOptType.HttpLogoutEvent.ordinal();
		mHandler.sendMessage(msg);
		
	}
	/**************************** IM Client Listener  **************************************/
	@Override
	public void OnLogin(LCC_ERR_TYPE errType, String errMsg) {
		Message msg = Message.obtain();
		msg.what = IMNotifyOptType.IMLoginEvent.ordinal();
		msg.arg1 = errType.ordinal();
		mHandler.sendMessage(msg);
		//事件分发通知
		mListenerManager.OnLogin(errType, errMsg);
	}

	/**
	 * 注销/断线回调
	 * @param errType
	 * @param errMsg
	 */
	@Override
	public void OnLogout(LCC_ERR_TYPE errType, String errMsg) {
		Message msg = Message.obtain();
		msg.what = IMNotifyOptType.IMLogoutEvent.ordinal();
		msg.arg1 = errType.ordinal();
		mHandler.sendMessage(msg);
		//事件分发通知
		mListenerManager.OnLogout(errType, errMsg);
	}

	@Override
	public void OnRoomIn(int reqId, boolean success, LCC_ERR_TYPE errType, String errMsg, IMRoomInItem roomInfo) {
		mListenerManager.OnRoomIn(reqId, success, errType, errMsg, roomInfo);
	}

	@Override
	public void OnRoomOut(int reqId, boolean success, LCC_ERR_TYPE errType, String errMsg) {
		mListenerManager.OnRoomOut(reqId, success, errType, errMsg);
	}

	@Override
	public void OnSendRoomMsg(int reqId, LCC_ERR_TYPE errType, String errMsg) {
		IMMessageItem msgItem = mSendingMsgMap.remove(Integer.valueOf(reqId));
		mListenerManager.OnSendRoomMsg(errType, errMsg, msgItem);
	}

	@Override
	public void OnSendGift(int reqId, boolean success, LCC_ERR_TYPE errType, String errMsg, double credit, double rebateCredit) {
		IMMessageItem msgItem = mSendingMsgMap.remove(Integer.valueOf(reqId));
		mListenerManager.OnSendGift(success, errType, errMsg, msgItem, credit, rebateCredit);
	}

	@Override
	public void OnSendBarrage(int reqId, boolean success, LCC_ERR_TYPE errType, String errMsg, double credit, double rebateCredit) {
		IMMessageItem msgItem = mSendingMsgMap.remove(Integer.valueOf(reqId));
		mListenerManager.OnSendBarrage(success, errType, errMsg, msgItem, credit, rebateCredit);
	}

	@Override
	public void OnSendImmediatePrivateInvite(int reqId, boolean success, LCC_ERR_TYPE errType, String errMsg, String inviteId) {
		mListenerManager.OnSendImmediatePrivateInvite(reqId, success, errType, errMsg, inviteId);
	}

	@Override
	public void OnCancelImmediatePrivateInvite(int reqId, boolean success, LCC_ERR_TYPE errType, String errMsg, String roomId) {
		mListenerManager.OnCancelImmediatePrivateInvite(reqId, success, errType, errMsg, roomId);
	}

	@Override
	public void OnKickOff() {
		mListenerManager.OnKickOff();
	}

	@Override
	public void OnRecvRoomCloseNotice(String roomId, String userId, String nickName) {
		mListenerManager.OnRecvRoomCloseNotice(roomId, userId, nickName);
	}

	@Override
	public void OnRecvEnterRoomNotice(String roomId, String userId, String nickName, String photoUrl, String riderId, String riderName, String riderUrl, int fansNum) {
		mListenerManager.OnRecvEnterRoomNotice(roomId, userId, nickName, photoUrl, riderId, riderName, riderUrl, fansNum);
	}

	@Override
	public void OnRecvLeaveRoomNotice(String roomId, String userId, String nickName, String photoUrl, int fansNum) {
		mListenerManager.OnRecvLeaveRoomNotice(roomId, userId, nickName, photoUrl, fansNum);
	}

	@Override
	public void OnRecvRebateInfoNotice(String roomId, IMRebateItem item) {
		mListenerManager.OnRecvRebateInfoNotice(roomId, item);
	}

	@Override
	public void OnRecvLeavingPublicRoomNotice(String roomId, LCC_ERR_TYPE err, String errMsg) {
		mListenerManager.OnRecvLeavingPublicRoomNotice(roomId, err, errMsg);
	}

	@Override
	public void OnRecvRoomKickoffNotice(String roomId, LCC_ERR_TYPE err, String errMsg, double credit) {
		mListenerManager.OnRecvRoomKickoffNotice(roomId, err, errMsg, credit);
	}

	@Override
	public void OnRecvLackOfCreditNotice(String roomId, String message, double credit) {
		mListenerManager.OnRecvLackOfCreditNotice(roomId, message, credit);
	}

	@Override
	public void OnRecvCreditNotice(String roomId, double credit) {
		mListenerManager.OnRecvCreditNotice(roomId, credit);
	}

	@Override
	public void OnRecvLiveStart(String roomId, int leftSeconds) {
		mListenerManager.OnRecvLiveStart(roomId, leftSeconds);
	}

	@Override
	public void OnRecvRoomMsg(String roomId, int level, String fromId, String nickName, String msg) {
		//收到普通文本消息
		IMMessageItem msgItem = new IMMessageItem(roomId, mMsgIdIndex.getAndIncrement(), fromId, nickName,
				level, IMMessageItem.MessageType.Normal, new IMTextMessageContent(msg), null);
		mListenerManager.OnRecvRoomMsg(msgItem);
		Log.i(TAG, "OnRecvRoomMsg msgId:%d, roomId:%s, userId:%s", msgItem.msgId, msgItem.roomId, msgItem.userId);
	}

	@Override
	public void OnRecvRoomGiftNotice(String roomId, String fromId, String nickName, String giftId, String giftName, int giftNum, boolean multi_click, int multi_click_start, int multi_click_end, int multiClickId) {
		IMGiftMessageContent msgContent = new IMGiftMessageContent(giftId, giftName, giftNum, multi_click, multi_click_start, multi_click_end, multiClickId);
		IMMessageItem msgItem = new IMMessageItem(roomId, mMsgIdIndex.getAndIncrement(), fromId, nickName, -1, IMMessageItem.MessageType.Gift, null, msgContent);
		mListenerManager.OnRecvRoomGiftNotice(msgItem);
		Log.i(TAG, "OnRecvRoomGiftNotice msgId:%d, roomId:%s, userId:%s", msgItem.msgId, msgItem.roomId, msgItem.userId);
	}

	@Override
	public void OnRecvRoomToastNotice(String roomId, String fromId, String nickName, String msg) {
		IMMessageItem msgItem = new IMMessageItem(roomId, mMsgIdIndex.getAndIncrement(), fromId, nickName,
				-1, IMMessageItem.MessageType.Barrage, new IMTextMessageContent(msg), null);
		mListenerManager.OnRecvRoomToastNotice(msgItem);
		Log.i(TAG, "OnRecvRoomGiftNotice msgId:%d, roomId:%s, userId:%s", msgItem.msgId, msgItem.roomId, msgItem.userId);
	}

	@Override
	public void OnRecvInviteReply(String inviteId, InviteReplyType replyType, String roomId) {
		mListenerManager.OnRecvInviteReply(inviteId, replyType, roomId);
	}

	@Override
	public void OnRecvAnchoeInviteNotify(String anchorId, String anchorName, String anchorPhotoUrl) {
		mListenerManager.OnRecvAnchoeInviteNotify(anchorId, anchorName, anchorPhotoUrl);
	}

	@Override
	public void OnRecvScheduledInviteNotify(String anchorId, String anchorName, String anchorPhotoUrl, int bookTime, String inviteId) {
		mListenerManager.OnRecvScheduledInviteNotify(anchorId, anchorName, anchorPhotoUrl, bookTime, inviteId);
	}


}