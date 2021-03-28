ifeq ($(BOARD_HAS_GPS),true)

LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_C_INCLUDES += \
	$(LOCAL_PATH) \
	$(LOCAL_PATH)/../include

LOCAL_SRC_FILES := gps.c
LOCAL_MODULE_TAGS := eng optional debug tests
LOCAL_MULTILIB := 64
LOCAL_SHARED_LIBRARIES := liblog libcutils libhardware
LOCAL_MODULE := gps.$(TARGET_BOARD_PLATFORM)
LOCAL_MODULE_PATH := $(TARGET_OUT_SHARED_LIBRARIES)/hw

include $(BUILD_SHARED_LIBRARY)
endif
