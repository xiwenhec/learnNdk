//
// Created by Sivin on 2018/3/1.
//

#include "common.h"
#include <stdio.h>

/**
 * 这个函数，我们从java层获取a,b然后将a,b 交换分离，最后将结果回传给java层
 * @param env
 * @param instance
 * @param a
 * @param b
 */

JNIEXPORT void JNICALL
Java_com_sivin_learnndk_lesson02_NativeApi02_changeValue(JNIEnv *env, jobject instance, jint a, jint b) {
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


/**
 * 本例演示的是JNI如何通过对象获取jclass进而调用这个类的静态函数
 * @param env
 * @param instance
 * @param str_
 */
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


/**
 * 我们知道静态函数是属于某个类的，并不属于某个对象，因此我们可以直接获取某个类，来调用这个静态函数
 * @param env
 * @param instance
 */
JNIEXPORT void JNICALL
Java_com_sivin_learnndk_lesson02_NativeApi02_callStaticMedthod2(JNIEnv *env, jobject instance) {

    //1.找到这个类的jclass
    jclass jclz = (*env)->FindClass(env,"");
}



/**
 * 这个函数的案例将会演示如何通过JNI层调用java某个类的构造函数，实例化出这个类对象，
 * 然后调用这个类对象的对象成员方法，和静态成员方法。
 * @param env
 * @param instance
 */
JNIEXPORT jobject JNICALL
Java_com_sivin_learnndk_lesson02_NativeApi02_callConstructMethd(JNIEnv *env, jobject instance) {

    //1.找到jclass,我们寻找Class可以通过这个类的对象，当我们没有这个类的对象时，我们该如何找到这个类呢？
    jclass jCourseClz = (*env)->FindClass(env,"com/sivin/learnndk/bean/Course");
    if(jCourseClz == NULL){
        LOGE("lesson02:callConstructMethod:%s","can't find course class");
        return NULL;
    }
    //2.得到构造方法的jMethodId,所有构造方法的名字都是"<init>"
    jmethodID jCourseMId = (*env)->GetMethodID(env,jCourseClz,"<init>","(Ljava/lang/String;I)V");
    //3.我们使用这个构造方法开始创建java对象,然后传入这个构造方法需要的参数。
    //这里我们需要注意 ，我们不能直接传入char*或者char[]类型的数据，而是应该传入JNI层的数据类型，由于基本类型可以直接传入
    //因此我们不用转换，但是我们需要将char*或者char[]转换成jstring传入，
    //至于释放内存方面我们，在后面在做讲解，此处我们暂不需要关心这里的功能。
    char name[10] ={0};
    sprintf(name,"%s","数学");
    jstring jName = (*env)->NewStringUTF(env,name);
    jobject jCourse = (*env)->NewObject(env,jCourseClz,jCourseMId,jName,100);
    (*env)->DeleteLocalRef(env,jName);
    if(jCourse == NULL){
        LOGE("lesson02:callConstructMethod:%s","can't create course obj");
        return NULL;
    }
    return jCourse;
}




