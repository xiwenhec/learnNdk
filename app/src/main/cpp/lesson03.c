//
// Created by Sivin on 2018/3/6.
//
#include "common.h"
#include <stdio.h>
#include <stdlib.h>


jint compare(const jint *a, const jint *b) {
    return *a - *b;
}

JNIEXPORT void JNICALL
Java_com_sivin_learnndk_lesson03_NativeApi03_sortArray(JNIEnv *env, jobject instance,
                                                       jintArray arr_) {
    //1.首先将jintArray转换成C/C++可以识别的数组，我们在C/C++中可以识别的int一般用int [] 或者int*
    jint *arr = (*env)->GetIntArrayElements(env, arr_, NULL);
    if (arr != NULL) {
        jsize len = (*env)->GetArrayLength(env, arr_);
        qsort(arr, len, sizeof(jint), compare);
        //第四个参数是mode:可以填写三种选择
        //0:表示对java数组更新数据，同时释放C++数组，
        //JNI_COMMIT：表示对java数组更新，同时不释放C/C++数组
        //JNI_ABORT:表示对java数组不更新，并释放C/C++数组
        (*env)->ReleaseIntArrayElements(env, arr_, arr, 0);
    }


    /**
     *
     */
    JNIEXPORT void JNICALL
    Java_com_sivin_learnndk_lesson03_NativeApi03_triggerDataCome(JNIEnv *env, jobject instance) {


    }


}