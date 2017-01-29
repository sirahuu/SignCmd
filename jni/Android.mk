LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := jp.sirahuu.mcpe.nativemod.signcmd 
LOCAL_SRC_FILES_RAW := $(shell find $(LOCAL_PATH) -name '*.cpp')
LOCAL_SRC_FILES := $(LOCAL_SRC_FILES_RAW:$(LOCAL_PATH)/%=%)

LOCAL_LDLIBS    := -L$(LOCAL_PATH) -llog -ldl -L$(LOCAL_PATH)/$(TARGET_ARCH_ABI) -lminecraftpe -lmcpelauncher_tinysubstrate

TARGET_NO_UNDEFINED_LDFLAGS :=

include $(BUILD_SHARED_LIBRARY)
