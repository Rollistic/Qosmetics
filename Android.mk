# Copyright (C) 2009 The Android Open Source Project
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.


LOCAL_PATH := $(call my-dir)
TARGET_ARCH_ABI := $(APP_ABI)

rwildcard=$(wildcard $1$2) $(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2))

# Creating prebuilt for dependency: beatsaber-hook - version: 1.0.9
include $(CLEAR_VARS)
LOCAL_MODULE := beatsaber-hook_1_0_9
LOCAL_EXPORT_C_INCLUDES := extern/beatsaber-hook
LOCAL_SRC_FILES := extern/libbeatsaber-hook_1_0_9.so
LOCAL_CPP_FEATURES += rtti exceptions
LOCAL_EXPORT_C_FLAGS := -DNEED_UNSAFE_CSHARP -Wno-inaccessible-base
include $(PREBUILT_SHARED_LIBRARY)
# Creating prebuilt for dependency: bs-utils - version: 0.5.5
include $(CLEAR_VARS)
LOCAL_MODULE := bs-utils
LOCAL_EXPORT_C_INCLUDES := extern/bs-utils
LOCAL_SRC_FILES := extern/libbs-utils.so
LOCAL_CPP_FEATURES += rtti exceptions
LOCAL_EXPORT_C_FLAGS := -Wno-inaccessible-base
include $(PREBUILT_SHARED_LIBRARY)
# Creating prebuilt for dependency: codegen - version: 0.5.3
include $(CLEAR_VARS)
LOCAL_MODULE := codegen_0_5_3
LOCAL_EXPORT_C_INCLUDES := extern/codegen
LOCAL_SRC_FILES := extern/libcodegen_0_5_3.so
LOCAL_CPP_FEATURES += rtti exceptions
LOCAL_EXPORT_C_FLAGS := -Wno-inaccessible-base
include $(PREBUILT_SHARED_LIBRARY)
# Creating prebuilt for dependency: custom-types - version: 0.4.2
include $(CLEAR_VARS)
LOCAL_MODULE := custom-types
LOCAL_EXPORT_C_INCLUDES := extern/custom-types
LOCAL_SRC_FILES := extern/libcustom-types.so
LOCAL_CPP_FEATURES += rtti exceptions
include $(PREBUILT_SHARED_LIBRARY)
# Creating prebuilt for dependency: questui - version: 0.3.2
include $(CLEAR_VARS)
LOCAL_MODULE := questui
LOCAL_EXPORT_C_INCLUDES := extern/questui
LOCAL_SRC_FILES := extern/libquestui.so
LOCAL_CPP_FEATURES += rtti exceptions
include $(PREBUILT_SHARED_LIBRARY)
# Creating prebuilt for dependency: modloader - version: 1.0.4
include $(CLEAR_VARS)
LOCAL_MODULE := modloader
LOCAL_EXPORT_C_INCLUDES := extern/modloader
LOCAL_SRC_FILES := extern/libmodloader.so
LOCAL_CPP_FEATURES += rtti exceptions
include $(PREBUILT_SHARED_LIBRARY)

# If you would like to use more shared libraries (such as custom UI, utils, or more) add them here, following the format above.
# In addition, ensure that you add them to the shared library build below.

include $(CLEAR_VARS)
LOCAL_MODULE := questcosmetics
LOCAL_SRC_FILES += $(call rwildcard,src/**,*.cpp)
LOCAL_SRC_FILES += $(call rwildcard,extern/beatsaber-hook/src/inline-hook,*.cpp)
LOCAL_SRC_FILES += $(call rwildcard,extern/beatsaber-hook/src/inline-hook,*.c)
LOCAL_SHARED_LIBRARIES += modloader
LOCAL_SHARED_LIBRARIES += beatsaber-hook_1_0_9
LOCAL_SHARED_LIBRARIES += codegen_0_5_3
LOCAL_SHARED_LIBRARIES += bs-utils
LOCAL_SHARED_LIBRARIES += custom-types
LOCAL_SHARED_LIBRARIES += questui
LOCAL_LDLIBS += -llog
LOCAL_CFLAGS += -I'D:/il2cpp/libil2cpp' -isystem 'extern' -I'extern/codegen/include' -DID='"Qosmetics"' -DVERSION='"1.UI"' -I'./shared' -I'./extern' -Wno-inaccessible-base -libcurl
LOCAL_C_INCLUDES += ./include ./src
include $(BUILD_SHARED_LIBRARY)
