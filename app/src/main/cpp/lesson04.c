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
Java_com_sivin_learnndk_lesson04_NativeApi04_demoLocalRef(JNIEnv *env, jobject instance) {
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



/**
 * 全局引用：GlobalRef
 * 创建全局引用的唯一方法：(*env)->NewGlobalRef(env,jobj);
 * 第二个参数是一个局部引用，是我们想要将某个对象，转换成全局引用，全局引用是夸线程的。
 * 创建了全局引用，必须要手动释放，否则会引起内存泄露。
 * @param env
 * @param instance
 */
jstring globalRefJstr;
JNIEXPORT void JNICALL
Java_com_sivin_learnndk_lesson04_NativeApi04_createGlobalRef(JNIEnv *env, jobject instance) {

    jobject jobj = (*env)->NewStringUTF(env,"hello");
    globalRefJstr = (*env)->NewGlobalRef(env,jobj);
}

/**
 * 释放全局引用
 * @param env
 * @param instance
 */
JNIEXPORT void JNICALL
Java_com_sivin_learnndk_lesson04_NativeApi04_deleteGlobalRef(JNIEnv *env, jobject instance) {
    (*env)->DeleteGlobalRef(env,globalRefJstr);
}


/**
 * 若全局引用，不会阻止GC,因此不用担心内存泄露
 * 若全局引用，也是夸线程的。
 * 一般的情况下，当我们定义一个引用，这个引用我们无法确定这个引用会不会阻止gc回收，这时我们就应该定义成若全局引用
 */
jclass g_weak_cls;
JNIEXPORT void JNICALL
Java_com_sivin_learnndk_lesson04_NativeApi04_createWeakRef(JNIEnv *env, jobject instance) {
    jclass cls = (*env)->FindClass(env,"java/lang/String");
    g_weak_cls = (*env)->NewWeakGlobalRef(env,cls);

}

