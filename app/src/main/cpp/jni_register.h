//
// Created by Sivin on 2018/3/17.
//

#ifndef LEARNNDK_JNI_REGISTER_H
#define LEARNNDK_JNI_REGISTER_H

#include <jni.h>
extern JNIEXPORT jstring JNICALL testDynamicRegister(JNIEnv *, jobject);
extern JNIEXPORT void JNICALL createThread(JNIEnv *, jobject);

#endif //LEARNNDK_JNI_REGISTER_H
