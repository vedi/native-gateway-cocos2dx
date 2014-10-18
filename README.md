Native Gateway Cocos2dx
---

It's Cocos2dx implementation of Native Gateway.

Native Gateway
---

Native Gateway allows you to create flexible native extension for cross-platform engines in easy way.


Getting Started
---

### iOS

Drag&Drop repository folder to your project in XCode.


### Android

1. In `Android.mk` of your project:
* include files from `cocos2dx` folder to your sources,
* add `cocos2d/cocos/platform/android/jni` to your `LOCAL_C_INCLUDES` (`LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../cocos2d/cocos/platform/android/jni`)
2. Add files from `android` folder to `libs` of your project.

### General Hints

1. Add repository as submodule of your project typing in your `Classes` folder:
```
git submodule add https://github.com/vedi/native-gateway-cocos2dx.git native-gateway
```
2. Create static links for jars in `proj.android/libs` instead of copying:
```
ln -s ../../Classes/native-gateway/android/native-gateway-cocos2dx.jar native-gateway-cocos2dx.jar
ln -s ../../Classes/native-gateway/android/native-gateway-common.jar native-gateway-common.jar
```


Configuration
---

This package by itself does not need any configuration efforts, it's just a core library of Native Gateway.

Related projects
---

This repository includes prebuild native libraries, the sources are available at the following URLs:
* https://github.com/vedi/native-gateway-common-android
* https://github.com/vedi/native-gateway-cocos2dx-android
* https://github.com/vedi/native-gateway-common-ios
* https://github.com/vedi/native-gateway-cocos2dx-ios
