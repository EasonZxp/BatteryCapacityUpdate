#include "com_example_myapplication_UsbGadgetHid.h"
#include "android/log.h"

static const char *TAG = "usb_gadget_hid_jni";
#define LOGI(fmt, args...) __android_log_print(ANDROID_LOG_INFO,  TAG, fmt, ##args)
#define LOGD(fmt, args...) __android_log_print(ANDROID_LOG_DEBUG, TAG, fmt, ##args)
#define LOGE(fmt, args...) __android_log_print(ANDROID_LOG_ERROR, TAG, fmt, ##args)
extern "C" {
extern int usbHidSend(uint8_t cmd, uint8_t *payload, uint8_t payloadLen);
extern int openDevNode();
extern void closeDevNode();
}
/*
 * Class:     com_example_myapplication_UsbGadgetHid
 * Method:    open
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_com_example_myapplication_UsbGadgetHid_open
  (JNIEnv *env, jobject obj)
  {
    return openDevNode();
  }

/*
 * Class:     com_example_myapplication_UsbGadgetHid
 * Method:    close
 * Signature: ()I
 */
JNIEXPORT void JNICALL Java_com_example_myapplication_UsbGadgetHid_close
  (JNIEnv *env, jobject obj){
    closeDevNode();
  }

  JNIEXPORT jint JNICALL Java_com_example_myapplication_UsbGadgetHid_hidSend
    (JNIEnv *env, jobject obj, jbyte cmd, jbyteArray payload){
       int ret = 0;
       uint8_t payloadLen = 0;
       uint8_t *payloadBuf = NULL;

       jbyte* jPayload = env->GetByteArrayElements(payload, 0);
       payloadLen = env->GetArrayLength(payload);
       payloadBuf = (uint8_t*)jPayload;
       ret = usbHidSend(cmd, payloadBuf, payloadLen);
       env->ReleaseByteArrayElements(payload, jPayload, 0);

       return ret;
    }