//
// Created by Sivin on 2018/3/10.
//

#include "common.h"


/**
 * 如果在JNI里出现了异常，此时JNI的代码会走完，但是java层就无法执行
 * 那么入如果我们在C层遇到了异常，但是我们想要在java层继续运行，我们改如何执行呢？
 * 这里我们可以清空，然后返回，这样就不影响java层运行了。
 *
 *
 * @param env
 * @param instance
 */
JNIEXPORT void JNICALL
Java_com_sivin_learnndk_lesson05_NativeApi05_jniCreateException(JNIEnv *env, jobject instance) {

    jclass cls = (*env)->GetObjectClass(env,instance);

    jfieldID fid = (*env)->GetFieldID(env,cls,"key","Ljava/lang/String;");


    jthrowable ex = (*env)->ExceptionOccurred(env);
    //判断异常是否发生
    if(ex != NULL){
        //这里我们清空 JNI产生的异常
        (*env)->ExceptionClear(env);

        //如果只是清空异常，显然不是试用所有情况，此时我们可以自己手动创建一个异常抛给java层
        jclass newExc = (*env)->FindClass(env,"java/lang/IllegalArgumentException");

        if(newExc == NULL){
            LOGE("lesson05:","out of memory");
            return ;
        }
        (*env)->ThrowNew(env,newExc,"jniCreateException occur a exception");
    }
}


