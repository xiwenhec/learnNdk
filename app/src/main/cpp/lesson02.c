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
    jclass jclz = (*env)->GetObjectClass(env, instance);

    //2.获取这个对象的方法id
    jmethodID jMid = (*env)->GetMethodID(env, jclz, "onNativeCallback", "(IILjava/lang/String;)V");

    jstring newJstr = (*env)->NewStringUTF(env, "success form JNI");
    //3.调用这个函数
    (*env)->CallVoidMethod(env, instance, jMid, temp_b, temp_a, newJstr);
}


int isNum(char num) {
    if ('0' <= num && num <= '9') {
        return 1;
    } else {
        return 0;
    }
}


int getNum(int array[], int len) {
    int sum = 0;
    int a = 1;
    for (int i = len - 1; i >= 0; i--) {
        sum += array[i] * a;
        a = a * 10;
    }
    return sum;
}

/**
 * 获取数字
 * @param src
 * @param left
 * @param right
 */
void getFactor(const char *src, int *left, int *right, char *oper) {

    int leftTemp[6] = {-1};
    int leftRealLen = 0;
    int rightTemp[6] = {-1};
    int rightRealLen = 0;
    int *temp = leftTemp;
    int index = 0;

    char *p = src;


    while ((*p) != NULL) {

        if (isNum((*p))) {
            temp[index] = ((*p) - '0');
        } else {
            leftRealLen = index;
            temp = rightTemp;
            *oper = (*p);
            p++;
            index = 0;
            continue;
        }
        p++;
        index++;
    }
    rightRealLen = index;

    *left = getNum(leftTemp, leftRealLen);
    *right = getNum(rightTemp, rightRealLen);

}


JNIEXPORT void JNICALL
Java_com_sivin_learnndk_lesson02_NativeApi02_calcuateStr(JNIEnv *env, jobject instance,
                                                         jstring str_) {
    int value = 0;

    const char *str = (*env)->GetStringUTFChars(env, str_, NULL);

    int leftFactor = 0, rightFactor = 0;

    int opertor = 0;

    getFactor(str, &leftFactor, &rightFactor, &opertor);


    char operArr[2] = {0};

    switch (opertor) {

        case '+':
            value = leftFactor + rightFactor;
            operArr[1] = '+';
            break;

        case '-':
            value = leftFactor - rightFactor;
            operArr[1] = '1';
            break;
    }

    jclass jclz = (*env)->GetObjectClass(env, instance);

    jmethodID jmdId = (*env)->GetStaticMethodID(env, jclz, "onNativeStaticCallback",
                                                "(ILjava/lang/String;)V");

    jstring joper = (*env)->NewStringUTF(env, operArr);

    (*env)->CallStaticVoidMethod(env,jclz,jmdId,value,joper);

    (*env)->ReleaseStringUTFChars(env, str_, str);
}