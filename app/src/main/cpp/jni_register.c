//
// Created by Sivin on 2018/3/17.
//

#include "common.h"
#include "jni_register.h"
#include <assert.h>
#ifndef NELEM
#define NELEM(x) ((sizeof(x) / sizeof((x)[0])))
#endif

JavaVM* g_vm = NULL;

static JNINativeMethod g_methods06[] = {
        { "testDynamicRegister", "()Ljava/lang/String;", (void *) testDynamicRegister}
};

static JNINativeMethod g_methods07[] = {
        { "createThread", "()V", (void *) createThread}
};





static int registerNativeMethods06(JNIEnv *env){
    LOGD("register native methods begin");
    jclass clz = (*env)->FindClass(env,"com/sivin/learnndk/lesson06/NativeApi06");
    if(clz == NULL){
        LOGE("can not find NativeApi06's class on register native methods");
        return JNI_FALSE;
    }
    assert(clz != NULL);
    /**
     * 向class参数指定的类注册本地方法，
     * g_methods06：这个class类中的需要注册的本地方法数组，
     * 第三个参数表示：g_methods06的数组大小，表示是方法的个数。
     * C/C++编程，数组作为形式参数时，会退化成指针，因此传递数组的时候，一般也会将该数组的大小也传递过去。
     * 这个函数执行成功返回0，执行失败返回负数。
     */
    if((*env)->RegisterNatives(env,clz,g_methods06,NELEM(g_methods06))<0){
        LOGE("register native methods07 fail");
        return JNI_FALSE;
    }
    return JNI_TRUE;
}


static int registerNativeMethods07(JNIEnv *env){
    LOGD("register native methods begin");
    jclass clz = (*env)->FindClass(env,"com/sivin/learnndk/lesson07/NativeApi07");
    if(clz == NULL){
        LOGE("can not find NativeApi07's class on register native methods");
        return JNI_FALSE;
    }
    assert(clz != NULL);
    /**
     * 向class参数指定的类注册本地方法，
     * g_methods06：这个class类中的需要注册的本地方法数组，
     * 第三个参数表示：g_methods06的数组大小，表示是方法的个数。
     * C/C++编程，数组作为形式参数时，会退化成指针，因此传递数组的时候，一般也会将该数组的大小也传递过去。
     * 这个函数执行成功返回0，执行失败返回负数。
     */
    if((*env)->RegisterNatives(env,clz,g_methods07,NELEM(g_methods07))<0){
        LOGE("register native methods07 fail");
        return JNI_FALSE;
    }
    return JNI_TRUE;
}



JNIEXPORT jint JNI_OnLoad(JavaVM* vm, void* reserved){
    g_vm = vm;
    jint result06 = JNI_FALSE , result07 = JNI_FALSE;
    JNIEnv *env = NULL;
    if((*vm)->GetEnv(vm,(void **)&env,JNI_VERSION_1_4) != JNI_OK){
        return JNI_FALSE;
    }
    assert(env != NULL);
    result06 = registerNativeMethods06(env);
    result07 = registerNativeMethods07(env);
    if(result06 == JNI_FALSE || result07 == JNI_FALSE){
        return JNI_FALSE;
    }else{
        return JNI_VERSION_1_4;
    }
}