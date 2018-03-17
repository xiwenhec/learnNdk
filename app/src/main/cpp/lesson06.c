//
// Created by Sivin on 2018/3/10.
//

#include "common.h"

JNIEXPORT jstring JNICALL testDynamicRegister(JNIEnv *env, jobject instance) {

    return (*env)->NewStringUTF(env, "动态注册测试成功");
}








