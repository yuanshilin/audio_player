## 简易音频播放器

#### 编译
```shell
export ANDROID_NDK=~/Android/ndk/android-ndk-r23
mkdir android_build && cd android_build

cmake -DCMAKE_TOOLCHAIN_FILE=$ANDROID_NDK/build/cmake/android.toolchain.cmake \
	-DANDROID_ABI="arm64-v8a" \
	-DANDROID_PLATFORM=android-29 \
	-DCMAKE_SYSTEM_NAME=Android \
	-DCMAKE_BUILD_TYPE=RELEASE \
	../
```



#### 参考资料
+ [《AAudio》](https://developer.android.com/ndk/guides/audio/aaudio/aaudio?hl=zh-cn) AAudio 是在 Android O 版本中引入的全新 Android C API。此 API 专为需要低延迟的高性能音频应用而设计。应用通过读取数据并将数据写入流来与 AAudio 进行通信。