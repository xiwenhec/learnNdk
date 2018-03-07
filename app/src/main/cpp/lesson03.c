//
// Created by Sivin on 2018/3/6.
//
#include "common.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>






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
}




JNIEXPORT void JNICALL
Java_com_sivin_learnndk_lesson03_NativeApi03_triggerData(JNIEnv *env, jobject instance) {

    //1.创建一个字符串
    char *str = "这个是C语言的字符串";
    //计算字符串的长度，就是字节数
    size_t num = strlen(str);

    //我们申请一块内存空间,由于java中字符串编码出现多余的时候会出现乱码，因此需要准确的将有效字符复制获取
    jbyte* jbStr = malloc(num * sizeof(jchar));
    memset(jbStr,0,num);
    memccpy(jbStr,str,0,num);

    //创建JbyteArray对象，并设置JArray对象的值
    jbyteArray jbArr = (*env)->NewByteArray(env,num);
    (*env)->SetByteArrayRegion(env,jbArr,0,num,jbStr);
    //释放创建的内存C/C++创建的内存空间
    free(jbStr);


    jclass jClz = (*env)->GetObjectClass(env,instance);
    if(jClz == NULL){
        LOGE("lesson03:%s","无法获取jclz");
        return;
    }
    jmethodID jmId = (*env)->GetMethodID(env,jClz,"onDataCome","([B)V");
    if(jmId == NULL){
        LOGE("lesson03:%s","无法获取jmId");
        return ;
    }
    (*env)->DeleteLocalRef(env,jClz);

    (*env)->CallVoidMethod(env,instance,jmId,jbArr);

}
