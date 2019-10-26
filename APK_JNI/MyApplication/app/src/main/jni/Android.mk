LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE := libusbhid_protocol
LOCAL_SRC_FILES := libusbhid_protocol.so
include $(PREBUILT_SHARED_LIBRARY)

include $(CLEAR_VARS)
# NDK_APP_DST_DIR=../../../../../SharedLibs/$(TARGET_ARCH_ABI)
LOCAL_MODULE := UsbGadgetHidJni
LOCAL_SRC_FILES := UsbGadgetHid.cpp
#LOCAL_CFLAGS += -fPIE
#LOCAL_LDFLAGS += -fPIE -pie
LOCAL_LDLIBS    := -llog
LOCAL_SHARED_LIBRARIES := \
    libusbhid_protocol
include $(BUILD_SHARED_LIBRARY)