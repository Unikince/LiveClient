//
//  ZBLiveChatManagerListener.h
//  dating
//
//  Created by  Samson on 5/16/16.
//  Copyright © 2016 qpidnetwork. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "ZBImHeader.h"

@protocol ZBIMLiveRoomManagerDelegate <NSObject>
@optional

#pragma mark - 登录/注销回调
/**
 *  登录回调
 *
 *  @param errType     结果类型
 *  @param errmsg      结果描述
 *  @param item        登录返回结构体
 */
- (void)onZBLogin:(ZBLCC_ERR_TYPE)errType errMsg:(NSString* _Nonnull)errmsg item:(ZBImLoginReturnObject* _Nonnull)item;

/**
 *  注销回调
 *
 *  @param errType     结果类型
 *  @param errmsg      结果描述
 */
- (void)onZBLogout:(ZBLCC_ERR_TYPE)errType errMsg:(NSString* _Nonnull)errmsg;

/**
 *  2.4.用户被挤掉线回调
 *
 *  @param errType     结果类型
 *  @param errmsg      结果描述
 */
- (void)onZBKickOff:(ZBLCC_ERR_TYPE)errType errMsg:(NSString* _Nonnull)errmsg;

//#pragma mark - 直播间主动操作回调
/**
 *  3.2.主播进入指定直播间回调
 *
 *  @param success     操作是否成功
 *  @param reqId       请求序列号
 *  @param errType     结果类型
 *  @param errmsg      结果描述
 *  @param item         直播间信息
 *
 */
- (void)onZBRoomIn:(BOOL)success reqId:(SEQ_T)reqId errType:(ZBLCC_ERR_TYPE)errType errMsg:(NSString* _Nonnull)errmsg item:(ZBImLiveRoomObject* _Nonnull)item;
/**
 *  3.3.主播退出直播间回调
 *
 *  @param success     操作是否成功
 *  @param reqId       请求序列号
 *  @param errType     结果类型
 *  @param errmsg      结果描述
 *
 */
- (void)onZBRoomOut:(BOOL)success reqId:(SEQ_T)reqId errType:(ZBLCC_ERR_TYPE)errType errMsg:(NSString* _Nonnull)errmsg;
//
/**
 *  3.1.新建/进入公开直播间接口 回调
 *
 *  @param success      操作是否成功
 *  @param reqId        请求序列号
 *  @param item         直播间信息
 *
 */
- (void)onZBPublicRoomIn:(SEQ_T)reqId success:(BOOL)success err:(ZBLCC_ERR_TYPE)err errMsg:(NSString* _Nonnull)errMsg item:(ZBImLiveRoomObject* _Nonnull)item;
//
///**
// *  3.14.观众开始／结束视频互动接口 回调
// *
// *  @param success          操作是否成功
// *  @param reqId            请求序列号
// *  @param errMsg           结果描述
// *  @param manPushUrl       观众视频流url
// *
// */
//- (void)onControlManPush:(SEQ_T)reqId success:(BOOL)success err:(LCC_ERR_TYPE)err errMsg:(NSString* _Nonnull)errMsg manPushUrl:(NSArray<NSString *> *_Nonnull)manPushUrl;
//


//#pragma mark - 直播间接收操作回调
/**
 *  3.4.接收直播间关闭通知(观众)回调
 *
 *  @param roomId      直播间ID
 *
 */
- (void)onZBRecvRoomCloseNotice:(NSString* _Nonnull)roomId errType:(ZBLCC_ERR_TYPE)errType errMsg:(NSString* _Nonnull)errmsg;


/**
 *  3.5.接收踢出直播间通知回调
 *
 *  @param roomId      直播间ID
 *  @param errType     踢出原因错误码
 *  @param errmsg      踢出原因描述
 *
 */
- (void)onZBRecvRoomKickoffNotice:(NSString* _Nonnull)roomId errType:(ZBLCC_ERR_TYPE)errType errmsg:(NSString* _Nonnull)errmsg;

/**
 *  3.6.接收观众进入直播间通知回调
 *
 *  @param roomId      直播间ID
 *  @param userId      观众ID
 *  @param nickName    观众昵称
 *  @param photoUrl    观众头像url
 *  @param riderId     座驾ID
 *  @param riderName   座驾名称
 *  @param riderUrl    座驾图片url
 *  @param fansNum     观众人数
 *
 */
- (void)onZBRecvEnterRoomNotice:(NSString* _Nonnull)roomId userId:(NSString* _Nonnull)userId nickName:(NSString* _Nonnull)nickName photoUrl:(NSString* _Nonnull)photoUrl riderId:(NSString* _Nonnull)riderId riderName:(NSString* _Nonnull)riderName riderUrl:(NSString* _Nonnull)riderUrl fansNum:(int)fansNum;

/**
 *  3.7.接收观众退出直播间通知回调
 *
 *  @param roomId      直播间ID
 *  @param userId      观众ID
 *  @param nickName    观众昵称
 *  @param photoUrl    观众头像url
 *  @param fansNum     观众人数
 *
 */
- (void)onZBRecvLeaveRoomNotice:(NSString* _Nonnull)roomId userId:(NSString* _Nonnull)userId nickName:(NSString* _Nonnull)nickName photoUrl:(NSString* _Nonnull)photoUrl fansNum:(int)fansNum;

/**
 *  3.8.接收关闭直播间倒数通知回调
 *
 *  @param roomId      直播间ID
 *  @param leftSeconds 关闭直播间倒数秒数（整型）（可无，无或0表示立即关闭）
 *  @param err         错误码
 *  @param errMsg      错误描述
 *
 */
- (void)onZBRecvLeavingPublicRoomNotice:(NSString* _Nonnull)roomId leftSeconds:(int)leftSeconds err:(ZBLCC_ERR_TYPE)err errMsg:(NSString* _Nonnull)errMsg;


#pragma mark - 直播间文本消息信息
/**
 *  4.1.发送直播间文本消息回调
 *
 *  @param reqId       请求序列号
 *  @param errType     结果类型
 *  @param errmsg      结果描述
 *
 */
- (void)onZBSendLiveChat:(BOOL)success reqId:(SEQ_T)reqId errType:(ZBLCC_ERR_TYPE)errType errMsg:(NSString* _Nonnull)errmsg;
/**
 *  4.2.接收直播间文本消息通知回调
 *
 *  @param roomId      直播间ID
 *  @param level       发送方级别
 *  @param fromId      发送方的用户ID
 *  @param nickName    发送方的昵称
 *  @param msg         文本消息内容
 *  @param honorUrl    勋章图片url
 *
 */
- (void)onZBRecvSendChatNotice:(NSString* _Nonnull)roomId level:(int)level fromId:(NSString* _Nonnull)fromId nickName:(NSString* _Nonnull)nickName msg:(NSString* _Nonnull)msg honorUrl:(NSString* _Nonnull)honorUrl;

/**
 *  4.3.接收直播间公告消息回调
 *
 *  @param roomId      直播间ID
 *  @param msg         公告消息内容
 *  @param link        公告链接（可无，无则表示不是带链接的公告消息）（仅当type=0有效）
 *  @param type        公告类型（0：普通，1：警告）
 *
 */
- (void)onZBRecvSendSystemNotice:(NSString* _Nonnull)roomId msg:(NSString* _Nonnull)msg link:(NSString* _Nonnull)link type:(ZBIMSystemType)type;

#pragma mark - 直播间礼物消息操作回调
/**
 *  5.1.发送直播间礼物消息（观众端发送直播间礼物消息，包括连击礼物）回调
 *
 *  @param success       操作是否成功
 *  @param reqId         请求序列号
 *  @param errType       结果类型
 *  @param errmsg        结果描述
 *
 */
- (void)onZBSendGift:(BOOL)success reqId:(SEQ_T)reqId errType:(ZBLCC_ERR_TYPE)errType errMsg:(NSString* _Nonnull)errmsg;
/**
 * 5.2.接收直播间礼物通知（观众端／主播端接收直播间礼物消息，包括连击礼物）回调
 *
 *  @param roomId               直播间ID
 *  @param fromId               发送方的用户ID
 *  @param nickName             发送方的昵称
 *  @param giftId               礼物ID
 *  @param giftName             礼物名称
 *  @param giftNum              本次发送礼物的数量
 *  @param multi_click          是否连击礼物
 *  @param multi_click_start    连击起始数
 *  @param multi_click_end      连击结束数
 *  @param multi_click_id       连击ID，相同则表示是同一次连击
 *  @param honorUrl             勋章图片url
 *
 */
- (void)onZBRecvSendGiftNotice:(NSString* _Nonnull)roomId fromId:(NSString* _Nonnull)fromId nickName:(NSString* _Nonnull)nickName giftId:(NSString* _Nonnull)giftId giftName:(NSString* _Nonnull)giftName giftNum:(int)giftNum multi_click:(BOOL)multi_click multi_click_start:(int)multi_click_start multi_click_end:(int)multi_click_end multi_click_id:(int)multi_click_id honorUrl:(NSString* _Nonnull)honorUrl totalCredit:(int)totalCredit;

#pragma mark - 直播间弹幕消息操作回调
/**
 *  6.1.接收直播间弹幕通知（观众端／主播端接收直播间弹幕消息）回调
 *
 *  @param roomId               直播间ID
 *  @param fromId               发送方的用户ID
 *  @param nickName             发送方的昵称
 *  @param msg                  消息内容
 *  @param honorUrl             勋章图片url
 *
 */
- (void)onZBRecvSendToastNotice:(NSString* _Nonnull)roomId fromId:(NSString* _Nonnull)fromId nickName:(NSString* _Nonnull)nickName msg:(NSString* _Nonnull)msg honorUrl:(NSString* _Nonnull)honorUrl;

// ------------- 直播间才艺点播邀请 -------------
/**
 *  7.1.接收直播间才艺点播邀请通知回调
 *  @param talentRequestItem             才艺点播请求
 *
 */
- (void)onZBRecvTalentRequestNotice:(ZBImTalentRequestObject* _Nonnull)talentRequestItem;

// ------------- 直播间视频互动 -------------
/**
 *  8.1.接收观众启动/关闭视频互动通知回调
 *
 *  @param Item            互动切换
 *
 */
- (void)onZBRecvControlManPushNotice:(ZBImControlPushItemObject * _Nonnull)Item;

#pragma mark - 邀请私密直播
/**
 *  9.1.主播发送立即私密邀请 回调
 *
 *  @param success       操作是否成功
 *  @param reqId         请求序列号
 *  @param err           结果类型
 *  @param errMsg        结果描述
 *  @param invitationId      邀请ID
 *  @param timeOut           邀请的剩余有效时间
 *  @param roomId            直播间ID
 *
 */
- (void) onZBSendImmediatePrivateInvite:(BOOL)success reqId:(SEQ_T)reqId err:(ZBLCC_ERR_TYPE)err errMsg:(NSString* _Nonnull)errMsg invitationId:(NSString* _Nonnull)invitationId timeOut:(int)timeOut roomId:(NSString* _Nonnull)roomId;

///**
// *  7.2.观众取消立即私密邀请 回调
// *
// *  @param success       操作是否成功
// *  @param reqId         请求序列号
// *  @param err           结果类型
// *  @param errMsg        结果描述
// *  @param roomId        直播间ID
// *
// */
//- (void)onSendCancelPrivateLiveInvite:(BOOL)success reqId:(SEQ_T)reqId err:(LCC_ERR_TYPE)err errMsg:(NSString* _Nonnull)errMsg roomId:(NSString* _Nonnull)roomId;
//
/**
 *  9.2.接收立即私密邀请回复通知 回调
 *
 *  @param inviteId      邀请ID
 *  @param replyType     主播回复 （0:拒绝 1:同意）
 *  @param roomId        直播间ID （可无，m_replyType ＝ 1存在）
 *  @param roomType      直播间类型
 *  @param userId        观众ID
 *  @param nickName      主播昵称
 *  @param avatarImg     主播头像
 *
 */
- (void)onZBRecvInstantInviteReplyNotice:(NSString* _Nonnull)inviteId replyType:(ZBReplyType)replyType roomId:(NSString* _Nonnull)roomId roomType:(ZBRoomType)roomType userId:(NSString* _Nonnull)userId nickName:(NSString* _Nonnull)nickName avatarImg:(NSString* _Nonnull)avatarImg;

/**
 *  9.3.接收立即私密邀请通知 回调
 *
 *  @param userId           观众ID
 *  @param nickName         观众昵称
 *  @param photoUrl         观众头像url
 *  @param invitationId     邀请ID
 *
 */
- (void)onZBRecvInstantInviteUserNotice:(NSString* _Nonnull)userId nickName:(NSString* _Nonnull)nickName photoUrl:(NSString* _Nonnull)photoUrl invitationId:(NSString* _Nonnull)invitationId;

/**
 *  9.4.接收预约开始倒数通知 回调
 *
 *  @param roomId       直播间ID
 *  @param userId       对端ID
 *  @param nickName     对端昵称
 *  @param avatarImg    对端头像url
 *  @param leftSeconds  倒数时间（秒）
 *
 */
- (void)onZBRecvBookingNotice:(NSString* _Nonnull)roomId userId:(NSString* _Nonnull)userId nickName:(NSString* _Nonnull)nickName avatarImg:(NSString* _Nonnull)avatarImg  leftSeconds:(int)leftSeconds;

/**
 *  9.5.获取指定立即私密邀请信息接口 回调
 *
 *  @param success          操作是否成功
 *  @param reqId            请求序列号
 *  @param errMsg           结果描述
 *  @param item             立即私密邀请
 *
 */
- (void)onZBGetInviteInfo:(SEQ_T)reqId success:(BOOL)success err:(ZBLCC_ERR_TYPE)err errMsg:(NSString* _Nonnull)errMsg item:(ZBImInviteIdItemObject *_Nonnull)item;

/**
 *  9.6.接收观众接受预约通知接口 回调
 *
 *  @param userId           观众ID
 *  @param nickName         观众昵称
 *  @param photoUrl         观众头像url
 *  @param invitationId     预约ID
 *  @param bookTime         预约时间（1970年起的秒数）
 */
- (void)onZBRecvInvitationAcceptNotice:(NSString* _Nonnull)userId nickName:(NSString* _Nonnull)nickName photoUrl:(NSString* _Nonnull)photoUrl invitationId:(NSString* _Nonnull)invitationId bookTime:(long)bookTime;

@end