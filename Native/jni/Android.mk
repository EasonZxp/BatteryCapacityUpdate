LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := usbhid_protocol

LOCAL_SRC_FILES := usbhid_protocol.c \
                   utils.c

LOCAL_CFLAGS += -fPIE
LOCAL_LDFLAGS += -fPIE -pie
LOCAL_LDLIBS    := -llog

#include $(BUILD_EXECUTABLE)
include $(BUILD_SHARED_LIBRARY)
