LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

ROOT_FILES  := $(wildcard $(LOCAL_PATH)/*.cpp)
ROOT_FILES  := $(ROOT_FILES:$(LOCAL_PATH)/%=%)

FRAMEWORK_MATH_FILES := $(wildcard $(LOCAL_PATH)/TaxiCode/Framework/Math/*.cpp)
FRAMEWORK_MATH_FILES := $(FRAMEWORK_MATH_FILES:$(LOCAL_PATH)/%=%)

FRAMEWORK_GRAPHICS_FILES := $(wildcard $(LOCAL_PATH)/TaxiCode/Framework/Graphics/*.cpp)
FRAMEWORK_GRAPHICS_FILES := $(FRAMEWORK_GRAPHICS_FILES:$(LOCAL_PATH)/%=%)
FRAMEWORK_GRAPHICS_FILES += TaxiCode/Framework/Graphics/Android/ImageLoader.cpp

FRAMEWORK_IO_FILES := $(wildcard $(LOCAL_PATH)/TaxiCode/Framework/IO/*.cpp)
FRAMEWORK_IO_FILES := $(FRAMEWORK_IO_FILES:$(LOCAL_PATH)/%=%)
FRAMEWORK_IO_FILES += TaxiCode/Framework/IO/Android/Path.cpp

FRAMEWORK_UTILS_FILES := $(wildcard $(LOCAL_PATH)/TaxiCode/Framework/Utils/*.cpp)
FRAMEWORK_UTILS_FILES := $(FRAMEWORK_UTILS_FILES:$(LOCAL_PATH)/%=%)
FRAMEWORK_UTILS_FILES += TaxiCode/Framework/Utils/Android/Log.cpp

FRAMEWORK_XML_FILES := $(wildcard $(LOCAL_PATH)/TaxiCode/Framework/XML/*.cpp)
FRAMEWORK_XML_FILES := $(FRAMEWORK_XML_FILES:$(LOCAL_PATH)/%=%)

EXT_TINYXML_FILES := $(wildcard $(LOCAL_PATH)/TaxiCode/Ext/tinyxml/*.cpp)
EXT_TINYXML_FILES := $(EXT_TINYXML_FILES:$(LOCAL_PATH)/%=%)

LOCAL_MODULE    := libtaxisoftlaunch
LOCAL_SRC_FILES := $(ROOT_FILES)
LOCAL_SRC_FILES += $(FRAMEWORK_MATH_FILES)
LOCAL_SRC_FILES += $(FRAMEWORK_IO_FILES)
LOCAL_SRC_FILES += $(FRAMEWORK_UTILS_FILES)
LOCAL_SRC_FILES += $(EXT_TINYXML_FILES)
LOCAL_SRC_FILES += $(FRAMEWORK_XML_FILES)
LOCAL_SRC_FILES += $(FRAMEWORK_GRAPHICS_FILES)

LOCAL_LDLIBS    := -llog -lGLESv2 -landroid

LOCAL_C_INCLUDES := $(LOCAL_PATH)/TaxiCode/Framework

include $(BUILD_SHARED_LIBRARY)
 
