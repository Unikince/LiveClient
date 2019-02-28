/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class com_qpidnetwork_livemodule_livechat_jni_LiveChatClient */

#ifndef _Included_com_qpidnetwork_livemodule_livechat_jni_LiveChatClient
#define _Included_com_qpidnetwork_livemodule_livechat_jni_LiveChatClient
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     com_qpidnetwork_livemodule_livechat_jni_LiveChatClient
 * Method:    SetLogDirectory
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_com_qpidnetwork_livemodule_livechat_jni_LiveChatClient_SetLogDirectory
  (JNIEnv *, jclass, jstring);

/*
 * Class:     com_qpidnetwork_livemodule_livechat_jni_LiveChatClient
 * Method:    Init
 * Signature: (Lcom/qpidnetwork/livechat/LiveChatClientListener;[Ljava/lang/String;I)Z
 */
JNIEXPORT jboolean JNICALL Java_com_qpidnetwork_livemodule_livechat_jni_LiveChatClient_Init
  (JNIEnv *, jclass, jobject, jobjectArray, jint);

/*
 * Class:     com_qpidnetwork_livemodule_livechat_jni_LiveChatClient
 * Method:    Login
 * Signature: (Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;I)Z
 */
JNIEXPORT jboolean JNICALL Java_com_qpidnetwork_livemodule_livechat_jni_LiveChatClient_Login
  (JNIEnv *, jclass, jstring, jstring, jstring, jint, jint);

/*
 * Class:     com_qpidnetwork_livemodule_livechat_jni_LiveChatClient
 * Method:    Logout
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_com_qpidnetwork_livemodule_livechat_jni_LiveChatClient_Logout
  (JNIEnv *, jclass);

/*
 * Class:     com_qpidnetwork_livemodule_livechat_jni_LiveChatClient
 * Method:    SetStatus
 * Signature: (I)Z
 */
JNIEXPORT jboolean JNICALL Java_com_qpidnetwork_livemodule_livechat_jni_LiveChatClient_SetStatus
  (JNIEnv *, jclass, jint);

/*
 * Class:     com_qpidnetwork_livemodule_livechat_jni_LiveChatClient
 * Method:    EndTalk
 * Signature: (Ljava/lang/String;)Z
 */
JNIEXPORT jboolean JNICALL Java_com_qpidnetwork_livemodule_livechat_jni_LiveChatClient_EndTalk
  (JNIEnv *, jclass, jstring);

/*
 * Class:     com_qpidnetwork_livemodule_livechat_jni_LiveChatClient
 * Method:    GetUserStatus
 * Signature: ([Ljava/lang/String;)Z
 */
JNIEXPORT jboolean JNICALL Java_com_qpidnetwork_livemodule_livechat_jni_LiveChatClient_GetUserStatus
  (JNIEnv *, jclass, jobjectArray);

/*
 * Class:     com_qpidnetwork_livemodule_livechat_jni_LiveChatClient
 * Method:    GetTalkInfo
 * Signature: (Ljava/lang/String;)Z
 */
JNIEXPORT jboolean JNICALL Java_com_qpidnetwork_livemodule_livechat_jni_LiveChatClient_GetTalkInfo
  (JNIEnv *, jclass, jstring);

/*
 * Class:     com_qpidnetwork_livemodule_livechat_jni_LiveChatClient
 * Method:    GetSessionInfo
 * Signature: (Ljava/lang/String;)Z
 */
JNIEXPORT jboolean JNICALL Java_com_qpidnetwork_livemodule_livechat_jni_LiveChatClient_GetSessionInfo
  (JNIEnv *, jclass, jstring);

/*
 * Class:     com_qpidnetwork_livemodule_livechat_jni_LiveChatClient
 * Method:    UploadTicket
 * Signature: (Ljava/lang/String;I)Z
 */
JNIEXPORT jboolean JNICALL Java_com_qpidnetwork_livemodule_livechat_jni_LiveChatClient_UploadTicket
  (JNIEnv *, jclass, jstring, jint);

/*
 * Class:     com_qpidnetwork_livemodule_livechat_jni_LiveChatClient
 * Method:    SendMessage
 * Signature: (Ljava/lang/String;Ljava/lang/String;ZII)Z
 */
JNIEXPORT jboolean JNICALL Java_com_qpidnetwork_livemodule_livechat_jni_LiveChatClient_SendMessage
  (JNIEnv *, jclass, jstring, jstring, jboolean, jint, jint);

/*
 * Class:     com_qpidnetwork_livemodule_livechat_jni_LiveChatClient
 * Method:    SendEmotion
 * Signature: (Ljava/lang/String;Ljava/lang/String;I)Z
 */
JNIEXPORT jboolean JNICALL Java_com_qpidnetwork_livemodule_livechat_jni_LiveChatClient_SendEmotion
  (JNIEnv *, jclass, jstring, jstring, jint);

/*
 * Class:     com_qpidnetwork_livemodule_livechat_jni_LiveChatClient
 * Method:    SendVGift
 * Signature: (Ljava/lang/String;Ljava/lang/String;I)Z
 */
JNIEXPORT jboolean JNICALL Java_com_qpidnetwork_livemodule_livechat_jni_LiveChatClient_SendVGift
  (JNIEnv *, jclass, jstring, jstring, jint);

/*
 * Class:     com_qpidnetwork_livemodule_livechat_jni_LiveChatClient
 * Method:    GetVoiceCode
 * Signature: (Ljava/lang/String;I)Z
 */
JNIEXPORT jboolean JNICALL Java_com_qpidnetwork_livemodule_livechat_jni_LiveChatClient_GetVoiceCode
  (JNIEnv *, jclass, jstring, jint);

/*
 * Class:     com_qpidnetwork_livemodule_livechat_jni_LiveChatClient
 * Method:    SendVoice
 * Signature: (Ljava/lang/String;Ljava/lang/String;II)Z
 */
JNIEXPORT jboolean JNICALL Java_com_qpidnetwork_livemodule_livechat_jni_LiveChatClient_SendVoice
  (JNIEnv *, jclass, jstring, jstring, jint, jint);

/*
 * Class:     com_qpidnetwork_livemodule_livechat_jni_LiveChatClient
 * Method:    SendMagicIcon
 * Signature: (Ljava/lang/String;Ljava/lang/String;I)Z
 */
JNIEXPORT jboolean JNICALL Java_com_qpidnetwork_livemodule_livechat_jni_LiveChatClient_SendMagicIcon
  (JNIEnv *, jclass, jstring, jstring, jint);

/*
 * Class:     com_qpidnetwork_livemodule_livechat_jni_LiveChatClient
 * Method:    UseTryTicket
 * Signature: (Ljava/lang/String;)Z
 */
JNIEXPORT jboolean JNICALL Java_com_qpidnetwork_livemodule_livechat_jni_LiveChatClient_UseTryTicket
  (JNIEnv *, jclass, jstring);

/*
 * Class:     com_qpidnetwork_livemodule_livechat_jni_LiveChatClient
 * Method:    GetTalkList
 * Signature: (I)Z
 */
JNIEXPORT jboolean JNICALL Java_com_qpidnetwork_livemodule_livechat_jni_LiveChatClient_GetTalkList
  (JNIEnv *, jclass, jint);

/*
 * Class:     com_qpidnetwork_livemodule_livechat_jni_LiveChatClient
 * Method:    SendPhoto
 * Signature: (Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;ZLjava/lang/String;I)Z
 */
JNIEXPORT jboolean JNICALL Java_com_qpidnetwork_livemodule_livechat_jni_LiveChatClient_SendPhoto
  (JNIEnv *, jclass, jstring, jstring, jstring, jstring, jboolean, jstring, jint);

/*
 * Class:     com_qpidnetwork_livemodule_livechat_jni_LiveChatClient
 * Method:    ShowPhoto
 * Signature: (Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;ZLjava/lang/String;I)Z
 */
JNIEXPORT jboolean JNICALL Java_com_qpidnetwork_livemodule_livechat_jni_LiveChatClient_ShowPhoto
  (JNIEnv *, jclass, jstring, jstring, jstring, jstring, jboolean, jstring, jint);

/*
 * Class:     com_qpidnetwork_livemodule_livechat_jni_LiveChatClient
 * Method:    PlayVideo
 * Signature: (Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;ZLjava/lang/String;I)Z
 */
JNIEXPORT jboolean JNICALL Java_com_qpidnetwork_livemodule_livechat_jni_LiveChatClient_PlayVideo
  (JNIEnv *, jclass, jstring, jstring, jstring, jstring, jboolean, jstring, jint);

/*
 * Class:     com_qpidnetwork_livemodule_livechat_jni_LiveChatClient
 * Method:    GetUserInfo
 * Signature: (Ljava/lang/String;)Z
 */
JNIEXPORT jboolean JNICALL Java_com_qpidnetwork_livemodule_livechat_jni_LiveChatClient_GetUserInfo
  (JNIEnv *, jclass, jstring);

/*
 * Class:     com_qpidnetwork_livemodule_livechat_jni_LiveChatClient
 * Method:    GetUsersInfo
 * Signature: ([Ljava/lang/String;)Z
 */
JNIEXPORT jboolean JNICALL Java_com_qpidnetwork_livemodule_livechat_jni_LiveChatClient_GetUsersInfo
  (JNIEnv *, jclass, jobjectArray);

/*
 * Class:     com_qpidnetwork_livemodule_livechat_jni_LiveChatClient
 * Method:    GetBlockList
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_com_qpidnetwork_livemodule_livechat_jni_LiveChatClient_GetBlockList
  (JNIEnv *, jclass);

/*
 * Class:     com_qpidnetwork_livemodule_livechat_jni_LiveChatClient
 * Method:    GetContactList
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_com_qpidnetwork_livemodule_livechat_jni_LiveChatClient_GetContactList
  (JNIEnv *, jclass);

/*
 * Class:     com_qpidnetwork_livemodule_livechat_jni_LiveChatClient
 * Method:    UploadVer
 * Signature: (Ljava/lang/String;)Z
 */
JNIEXPORT jboolean JNICALL Java_com_qpidnetwork_livemodule_livechat_jni_LiveChatClient_UploadVer
  (JNIEnv *, jclass, jstring);

/*
 * Class:     com_qpidnetwork_livemodule_livechat_jni_LiveChatClient
 * Method:    GetBlockUsers
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_com_qpidnetwork_livemodule_livechat_jni_LiveChatClient_GetBlockUsers
  (JNIEnv *, jclass);

/*
 * Class:     com_qpidnetwork_livemodule_livechat_jni_LiveChatClient
 * Method:    GetLadyCondition
 * Signature: (Ljava/lang/String;)Z
 */
JNIEXPORT jboolean JNICALL Java_com_qpidnetwork_livemodule_livechat_jni_LiveChatClient_GetLadyCondition
  (JNIEnv *, jclass, jstring);

/*
 * Class:     com_qpidnetwork_livemodule_livechat_jni_LiveChatClient
 * Method:    GetLadyCustomTemplate
 * Signature: (Ljava/lang/String;)Z
 */
JNIEXPORT jboolean JNICALL Java_com_qpidnetwork_livemodule_livechat_jni_LiveChatClient_GetLadyCustomTemplate
  (JNIEnv *, jclass, jstring);

/*
 * Class:     com_qpidnetwork_livemodule_livechat_jni_LiveChatClient
 * Method:    UploadPopLadyAutoInvite
 * Signature: (Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)Z
 */
JNIEXPORT jboolean JNICALL Java_com_qpidnetwork_livemodule_livechat_jni_LiveChatClient_UploadPopLadyAutoInvite
  (JNIEnv *, jclass, jstring, jstring, jstring);

/*
 * Class:     com_qpidnetwork_livemodule_livechat_jni_LiveChatClient
 * Method:    UploadAutoChargeStatus
 * Signature: (Z)Z
 */
JNIEXPORT jboolean JNICALL Java_com_qpidnetwork_livemodule_livechat_jni_LiveChatClient_UploadAutoChargeStatus
  (JNIEnv *, jclass, jboolean);

/*
 * Class:     com_qpidnetwork_livemodule_livechat_jni_LiveChatClient
 * Method:    GetPaidTheme
 * Signature: (Ljava/lang/String;)Z
 */
JNIEXPORT jboolean JNICALL Java_com_qpidnetwork_livemodule_livechat_jni_LiveChatClient_GetPaidTheme
  (JNIEnv *, jclass, jstring);

/*
 * Class:     com_qpidnetwork_livemodule_livechat_jni_LiveChatClient
 * Method:    GetAllPaidTheme
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_com_qpidnetwork_livemodule_livechat_jni_LiveChatClient_GetAllPaidTheme
  (JNIEnv *, jclass);

/*
 * Class:     com_qpidnetwork_livemodule_livechat_jni_LiveChatClient
 * Method:    UploadThemeListVer
 * Signature: (I)Z
 */
JNIEXPORT jboolean JNICALL Java_com_qpidnetwork_livemodule_livechat_jni_LiveChatClient_UploadThemeListVer
  (JNIEnv *, jclass, jint);

/*
 * Class:     com_qpidnetwork_livemodule_livechat_jni_LiveChatClient
 * Method:    ManFeeTheme
 * Signature: (Ljava/lang/String;Ljava/lang/String;)Z
 */
JNIEXPORT jboolean JNICALL Java_com_qpidnetwork_livemodule_livechat_jni_LiveChatClient_ManFeeTheme
  (JNIEnv *, jclass, jstring, jstring);

/*
 * Class:     com_qpidnetwork_livemodule_livechat_jni_LiveChatClient
 * Method:    ManApplyTheme
 * Signature: (Ljava/lang/String;Ljava/lang/String;)Z
 */
JNIEXPORT jboolean JNICALL Java_com_qpidnetwork_livemodule_livechat_jni_LiveChatClient_ManApplyTheme
  (JNIEnv *, jclass, jstring, jstring);

/*
 * Class:     com_qpidnetwork_livemodule_livechat_jni_LiveChatClient
 * Method:    PlayThemeMotion
 * Signature: (Ljava/lang/String;Ljava/lang/String;)Z
 */
JNIEXPORT jboolean JNICALL Java_com_qpidnetwork_livemodule_livechat_jni_LiveChatClient_PlayThemeMotion
  (JNIEnv *, jclass, jstring, jstring);

/*
 * class:      com_qpidnetwork_livemodule_livechat_jni_LiveChatClient
 * Method:     GetLadyCamStatus
 * Signature:  (Ljava/lang/String;)Z
 */
JNIEXPORT jboolean JNICALL Java_com_qpidnetwork_livemodule_livechat_jni_LiveChatClient_GetLadyCamStatus
  (JNIEnv *, jclass, jstring);

/*
 * Class:     com_qpidnetwork_livemodule_livechat_jni_LiveChatClient
 * Method:    SendCamShareInvite
 * Signature: (Ljava/lang/String;IILjava/lang/String;)Z
 */
JNIEXPORT jboolean JNICALL Java_com_qpidnetwork_livemodule_livechat_jni_LiveChatClient_SendCamShareInvite
  (JNIEnv *, jclass, jstring, jint, jint, jstring);

/*
 * Class:     com_qpidnetwork_livemodule_livechat_jni_LiveChatClient
 * Method:    ApplyCamShare
 * Signature: (Ljava/lang/String;)Z
 */
JNIEXPORT jboolean JNICALL Java_com_qpidnetwork_livemodule_livechat_jni_LiveChatClient_ApplyCamShare
  (JNIEnv *, jclass, jstring);

///*
// * Class:     com_qpidnetwork_livemodule_livechat_jni_LiveChatClient
// * Method:    LadyAcceptCamInvite
// * Signature: (Ljava/lang/String;Ljava/lang/String;Z)Z
// */
//JNIEXPORT jboolean JNICALL Java_com_qpidnetwork_livemodule_livechat_jni_LiveChatClient_LadyAcceptCamInvite
//  (JNIEnv *, jclass, jstring, jstring, jboolean);

/*
 * Class:     com_qpidnetwork_livemodule_livechat_jni_LiveChatClient
 * Method:    CamShareHearbeat
 * Signature: (Ljava/lang/String;Ljava/lang/String;)Z
 */
JNIEXPORT jboolean JNICALL Java_com_qpidnetwork_livemodule_livechat_jni_LiveChatClient_CamShareHearbeat
  (JNIEnv *, jclass, jstring, jstring);

/*
 * Class:     com_qpidnetwork_livemodule_livechat_jni_LiveChatClient
 * Method:    GetUsersCamStatus
 * Signature: ([Ljava/lang/String;)Z
 */
JNIEXPORT jboolean JNICALL Java_com_qpidnetwork_livemodule_livechat_jni_LiveChatClient_GetUsersCamStatus
  (JNIEnv *, jclass, jobjectArray);

/*
 * Class:     com_qpidnetwork_livemodule_livechat_jni_LiveChatClient
 * Method:    CamshareUseTryTicket
 * Signature: (Ljava/lang/String;Ljava/lang/String;)Z
 */
JNIEXPORT jboolean JNICALL Java_com_qpidnetwork_livemodule_livechat_jni_LiveChatClient_CamshareUseTryTicket
  (JNIEnv *, jclass, jstring, jstring);

#ifdef __cplusplus
}
#endif
#endif