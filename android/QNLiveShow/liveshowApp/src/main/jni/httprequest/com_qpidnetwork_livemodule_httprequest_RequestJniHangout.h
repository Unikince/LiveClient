/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class com_qpidnetwork_livemodule_httprequest_RequestJniHangout */

#ifndef _Included_com_qpidnetwork_livemodule_httprequest_RequestJniHangout
#define _Included_com_qpidnetwork_livemodule_httprequest_RequestJniHangout
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     com_qpidnetwork_livemodule_httprequest_RequestJniHangout
 * Method:    GetCanHangoutAnchorList
 * Signature: (ILjava/lang/String;IILcom/qpidnetwork/livemodule/httprequest/OnGetCanHangoutAnchorListCallback;)J
 */
JNIEXPORT jlong JNICALL Java_com_qpidnetwork_livemodule_httprequest_RequestJniHangout_GetCanHangoutAnchorList
  (JNIEnv *, jclass, jint, jstring , jint , jint, jobject);

/*
 * Class:     com_qpidnetwork_livemodule_httprequest_RequestJniHangout
 * Method:    SendInvitationHangout
 * Signature: (Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Lcom/qpidnetwork/livemodule/httprequest/OnSendInvitationHangoutCallback;)J
 */
JNIEXPORT jlong JNICALL Java_com_qpidnetwork_livemodule_httprequest_RequestJniHangout_SendInvitationHangout
  (JNIEnv *, jclass, jstring, jstring, jstring, jobject);

/*
 * Class:     com_qpidnetwork_livemodule_httprequest_RequestJniHangout
 * Method:    CancelHangoutInvit
 * Signature: (Ljava/lang/String;Lcom/qpidnetwork/livemodule/httprequest/OnRequestCallback;)J
 */
JNIEXPORT jlong JNICALL Java_com_qpidnetwork_livemodule_httprequest_RequestJniHangout_CancelHangoutInvit
  (JNIEnv *, jclass, jstring , jobject);

/*
 * Class:     com_qpidnetwork_livemodule_httprequest_RequestJniHangout
 * Method:    GetHangoutInvitStatus
 * Signature: (Ljava/lang/String;Lcom/qpidnetwork/livemodule/httprequest/OnGetHangoutInvitStatusCallback;)J
 */
JNIEXPORT jlong JNICALL Java_com_qpidnetwork_livemodule_httprequest_RequestJniHangout_GetHangoutInvitStatus
  (JNIEnv *, jclass, jstring, jobject);

/*
 * Class:     com_qpidnetwork_livemodule_httprequest_RequestJniHangout
 * Method:    DealKnockRequest
 * Signature: (Ljava/lang/String;Lcom/qpidnetwork/livemodule/httprequest/OnRequestCallback;)J
 */
JNIEXPORT jlong JNICALL Java_com_qpidnetwork_livemodule_httprequest_RequestJniHangout_DealKnockRequest
  (JNIEnv *, jclass, jstring, jobject);


/*
 * Class:     com_qpidnetwork_livemodule_httprequest_RequestJniHangout
 * Method:    DGetHangoutGiftList
 * Signature: (Ljava/lang/String;Lcom/qpidnetwork/livemodule/httprequest/OnGetHangoutGiftListCallback;)J
 */
JNIEXPORT jlong JNICALL Java_com_qpidnetwork_livemodule_httprequest_RequestJniHangout_GetHangoutGiftList
        (JNIEnv *, jclass, jstring, jobject);


#ifdef __cplusplus
}
#endif
#endif