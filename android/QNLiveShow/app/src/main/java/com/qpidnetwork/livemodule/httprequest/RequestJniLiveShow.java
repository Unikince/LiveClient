package com.qpidnetwork.livemodule.httprequest;

/**
 * 直播间相关接口
 * @author Hunter Mun
 * @since 2017-5-22
 */
public class RequestJniLiveShow {
	
	/**
	 * 3.1.分页获取热播列表
	 * @param start
	 * @param step
	 * @param callback
	 * @return
	 */
	static public native long GetHotLiveList(int start, int step, OnGetHotListCallback callback);
	
	/**
	 * 3.2.分页获取收藏主播当前开播列表
	 * @param start
	 * @param step
	 * @param callback
	 * @return
	 */
	static public native long GetFollowingLiveList(int start, int step, OnGetFollowingListCallback callback);
	
	/**
	 * 3.3.获取本人有效直播间或邀请信息
	 * @param callback
	 * @return
	 */
	static public native long GetLivingRoomAndInvites(OnGetLivingRoomAndInvitesCallback callback);
	
	/**
	 * 3.4.获取直播间观众头像列表
	 * @param roomId
	 * @param callback
	 * @return
	 */
	static public native long GetAudienceListInRoom(String roomId, OnGetAudienceListCallback callback);
	
	/**
	 * 3.5. 获取礼物列表
	 * @param callback
	 * @return
	 */
	static public native long GetAllGiftList(OnGetGiftListCallback callback);
	
	/**
	 * 3.6. 获取直播间可发送的礼物列表
	 * @param roomId
	 * @param callback
	 * @return
	 */
	static public native long GetSendableGiftList(String roomId, OnGetSendableGiftListCallback callback);
	
	/**
	 * 3.7. 获取指定礼物详情
	 * @param giftId
	 * @param callback
	 * @return
	 */
	static public native long GetGiftDetail(String giftId, OnGetGiftDetailCallback callback);
	
	/**
	 * 3.8.获取文本表情列表
	 * @param callback
	 * @return
	 */
	static public native long GetEmotionList(OnGetEmotionListCallback callback);
	
	/**
	 * 3.9.获取指定立即私密邀请信息
	 * @param inviteId
	 * @param callback
	 * @return
	 */
	static public native long GetImediateInviteInfo(String inviteId, OnGetImediateInviteInfoCallback callback);
}