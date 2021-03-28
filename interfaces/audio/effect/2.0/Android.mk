# This file is autogenerated by hidl-gen. Do not edit manually.

LOCAL_PATH := $(call my-dir)

################################################################################

include $(CLEAR_VARS)
LOCAL_MODULE := android.hardware.audio.effect-V2.0-java-constants
LOCAL_MODULE_CLASS := JAVA_LIBRARIES

intermediates := $(call local-generated-sources-dir, COMMON)

HIDL := $(HOST_OUT_EXECUTABLES)/hidl-gen$(HOST_EXECUTABLE_SUFFIX)
#
GEN := $(intermediates)/android/hardware/audio/effect/V2_0/Constants.java
$(GEN): $(HIDL)
$(GEN): $(LOCAL_PATH)/types.hal
$(GEN): $(LOCAL_PATH)/IAcousticEchoCancelerEffect.hal
$(GEN): $(LOCAL_PATH)/IAutomaticGainControlEffect.hal
$(GEN): $(LOCAL_PATH)/IBassBoostEffect.hal
$(GEN): $(LOCAL_PATH)/IDownmixEffect.hal
$(GEN): $(LOCAL_PATH)/IEffect.hal
$(GEN): $(LOCAL_PATH)/IEffectBufferProviderCallback.hal
$(GEN): $(LOCAL_PATH)/IEffectsFactory.hal
$(GEN): $(LOCAL_PATH)/IEnvironmentalReverbEffect.hal
$(GEN): $(LOCAL_PATH)/IEqualizerEffect.hal
$(GEN): $(LOCAL_PATH)/ILoudnessEnhancerEffect.hal
$(GEN): $(LOCAL_PATH)/INoiseSuppressionEffect.hal
$(GEN): $(LOCAL_PATH)/IPresetReverbEffect.hal
$(GEN): $(LOCAL_PATH)/IVirtualizerEffect.hal
$(GEN): $(LOCAL_PATH)/IVisualizerEffect.hal

$(GEN): PRIVATE_HIDL := $(HIDL)
$(GEN): PRIVATE_OUTPUT_DIR := $(intermediates)
$(GEN): PRIVATE_CUSTOM_TOOL = \
        $(PRIVATE_HIDL) -o $(PRIVATE_OUTPUT_DIR) \
        -Ljava-constants \
        -randroid.hardware:hardware/interfaces \
        -randroid.hidl:system/libhidl/transport \
        android.hardware.audio.effect@2.0

$(GEN):
	$(transform-generated-source)
LOCAL_GENERATED_SOURCES += $(GEN)
# Avoid dependency cycle of framework.jar -> this-library -> framework.jar
LOCAL_NO_STANDARD_LIBRARIES := true
LOCAL_JAVA_LIBRARIES := core-oj

include $(BUILD_STATIC_JAVA_LIBRARY)



include $(call all-makefiles-under,$(LOCAL_PATH))
