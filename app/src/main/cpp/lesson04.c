//
// Created by Sivin on 2018/3/8.
//
#include "common.h"






/**
 * 局部引用：
 * FindClass NewObject ,GetObjectClass ,NewCharArray....
 * 用来生成jvm对象类型数据都是用来局部引用来表示的
 * 这里我们要说明一下jmethodID 不是一个对象，是一个结构体，因此不能够转换成GlobalRef,也不用释放。
 *
 * JNI局部引用释放的方式有：1.方法调用玩，自动释放 。 2.手动释放
 *
 * 那么既然有了自动释放，为什么我们还要手动释放呢？
 *
 * 在jvm中内部为JNI维护这一个局部引用表，这个引用表里存放着当前JNI的调用的局部引用，这个表最多能存放512个局部引用
 *
 * 如果在函数调用的时候，如果在多线程的时候，如果没有及时释放局部引用，则可能导致局部引用表溢出。
 *
 *
 * 局部引用不能再多线程里面使用。
 *
 *
 */
JNIEXPORT jstring JNICALL
Java_com_sivin_learnndk_lesson04_NativeApi04_initStr(JNIEnv *env, jobject instance) {
    jclass jClz = (*env)->FindClass(env,"java/lang/String");
    jmethodID jmId = (*env)->GetMethodID(env,jClz,"<init>","(Ljava/lang/String;)V");

    jstring src = (*env)->NewStringUTF(env,"这是JNI创建的String对象");

    //调用java层的含有一个参数的构造方法，然后来创建一个String对象
    jstring jstr = (*env)->NewObject(env,jClz,jmId,src);
    //释放引用

    (*env)->DeleteLocalRef(env,src);
    (*env)->DeleteLocalRef(env,jClz);

    //这里我们因为要将这个引用返回，此时这个对象的内存就由JNI交给了Jvm自己管理了
    //(*env)->DeleteLocalRef(env,jstr);
    return jstr;
}