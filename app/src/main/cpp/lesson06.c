//
// Created by Sivin on 2018/3/10.
//

#include "common.h"
#include <assert.h>
#ifndef NELEM
#define NELEM(x) ((sizeof(x) / sizeof((x)[0])))
#endif



JNIEXPORT jstring JNICALL testDynamicRegister(JNIEnv *env, jobject instance) {

    return (*env)->NewStringUTF(env, "动态注册测试成功");
}




//1.首先将我们的native方法，放到数组中
static const JNINativeMethod gMethods[] = {
        "testDynamicRegister", "()Ljava/lang/String;", (void *) testDynamicRegister
};


//注册我们对应的层代码
static const int registerNatives(JNIEnv *env) {

    LOGD("register native begin");

    jclass cls = (*env)->FindClass(env,
                                   "com/sivin/learnndk/lessson06/NativeApi06");
    if (cls == NULL) {
        return JNI_FALSE;
    }
    if((*env)->RegisterNatives(env,cls,gMethods,NELEM(gMethods))<0){
        return JNI_FALSE;
    }
    return JNI_TRUE;
}


//这个地方是JNI开始加载的时候就该调用
JNIEXPORT jint JNI_OnLoad(JavaVM* vm, void* reserved){
    LOGD("JNI onLoad begin");

    JNIEnv* env = NULL;
    jint result = -1;

    if((*vm)->GetEnv(vm,(void **)&env,JNI_VERSION_1_4) != JNI_OK){
        LOGE("ERROR:GetEnv failed\n");
        return -1;
    }
    //断定这个地方env != NULL 如果断言不对，则程序退出
    assert(env != NULL);
    registerNatives(env);
    return JNI_VERSION_1_4;
}



