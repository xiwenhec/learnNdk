//
// Created by Sivin on 2018/3/1.
//

#ifndef LEARNNDK_COMMON_H
#define LEARNNDK_COMMON_H
#include <jni.h>
#include <android/log.h>
#define TAG "NDK"
#define LOGV(...) __android_log_print(ANDROID_LOG_VERBOSE, TAG, __VA_ARGS__)
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, TAG, __VA_ARGS__)
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, TAG, __VA_ARGS__)
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN, TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, TAG, __VA_ARGS__)
#endif //LEARNNDK_COMMON_H
