LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

ROOT_FILES  := $(wildcard $(LOCAL_PATH)/*.cpp)
ROOT_FILES  := $(ROOT_FILES:$(LOCAL_PATH)/%=%)

LOCAL_MODULE    := libtaxisoftlaunch
LOCAL_SRC_FILES := $(ROOT_FILES)
LOCAL_LDLIBS    := -llog -lGLESv2 -landroid

#LOCAL_C_INCLUDES := $(LOCAL_PATH)/sss

include $(BUILD_SHARED_LIBRARY)
 
