#ifndef  __UTILS_H
#define  __UTILS_H

uint16_t getCrc16Check(uint8_t *Buf, uint16_t Len);
uint16_t getCRC16Check(uint8_t *bufData, uint16_t len);

#include "android/log.h"

static const char *TAG="usb_gadget_hid";
#define LOGI(fmt, args...) __android_log_print(ANDROID_LOG_INFO,  TAG, fmt, ##args)
#define LOGD(fmt, args...) __android_log_print(ANDROID_LOG_DEBUG, TAG, fmt, ##args)
#define LOGE(fmt, args...) __android_log_print(ANDROID_LOG_ERROR, TAG, fmt, ##args)

#define DBG LOGI
#define ERROR LOGE

#endif
