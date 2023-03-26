#include <jni.h>
#include <android/log.h>
#include <cstring>
#include <cstdlib>
#include "MemoryUtil.h"

extern "C"
JNIEXPORT jlong JNICALL
Java_com_sivin_learnndk_utils_MemoryUtil_getAvailableMemeory(JNIEnv *env, jclass clazz) {
    MemInfo info{};
    bzero(&info, sizeof(info));
    get_system_meminfo(&info);
    return info.system_availableram;
}