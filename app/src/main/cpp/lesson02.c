//
// Created by Sivin on 2018/3/1.
//

#include "common.h"


/**
 * 这个函数，我们从java层获取a,b然后将a,b 交换分离，最后将结果回传给java层
 * @param env
 * @param instance
 * @param a
 * @param b
 */

JNIEXPORT void JNICALL
Java_com_sivin_learnndk_lesson02_NativeApi02_changeValue(JNIEnv *env, jobject instance, jint a,
                                                       jint b) {
    int32_t temp_b = a;
    int32_t temp_a = b;
    //1.获取这个对象的jclsss
    jclass jclz = (*env)->GetObjectClass(env,instance);

    //2.获取这个对象的方法id
    jmethodID jMid = (*env)->GetMethodID(env,jclz,"onNativeCallback","(IILjava/lang/String;)V");

    jstring newJstr = (*env)->NewStringUTF(env,"success form JNI");
    //3.调用这个函数
    (*env)->CallVoidMethod(env,instance,jMid,temp_b,temp_a,newJstr);
}