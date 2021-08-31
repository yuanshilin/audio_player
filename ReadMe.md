## 简易音频播放器

#### 编译
```shell
export ANDROID_NDK=~/Android/ndk/android-ndk-r23
mkdir android_build && cd android_build

# 编译的库直接被aosp内部代码引用有如下错误
# Unknown attribute kind (62) (Producer: 'LLVM12.0.5git' Reader: 'LLVM 9.0.3svn')

cmake -DCMAKE_TOOLCHAIN_FILE=$ANDROID_NDK/build/cmake/android.toolchain.cmake \
	-DANDROID_ABI="arm64-v8a" \
	-DANDROID_PLATFORM=android-28 \
	-DCMAKE_SYSTEM_NAME=Android \
	-DCMAKE_BUILD_TYPE=RELEASE \
	../
```

#### 内嵌在AOSP源码编译
支持Android.mk编译