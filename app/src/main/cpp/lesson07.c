#include "common.h"
#include "pthread.h"
#include <assert.h>

extern JavaVM *g_vm;

jobject globalApi07Obj;
//这里也充分证明了 j_mid是可以跨线程使用的
//官方文档也给了充分的说明:Method and field IDs are regular C pointer types,是常规的指针类型
jmethodID j_mid;

void threadFun(void *i);

/**
 * 本例子，我们使用这个函数来触发创建多个线程的代码，然后执行相关的信息。
 * 比如我们让子线程的代码，来回调我们的上层的java函数。
 *
 * 我们知道，想要回调上层的函数，我们一般调用Call***Method函数，这里我们就看看如何操作
 * @param env
 * @param instance
 */
JNIEXPORT void JNICALL createThread(JNIEnv *env, jobject instance) {
    LOGD("lesson07:createThread perform\n");

    //保存这个对象,以便其他线程使用,instance是一个LocalRef对象,无法跨线程,因此我们需要保存成为GlobalRef
    globalApi07Obj = (*env)->NewGlobalRef(env, instance);
    jclass cls = (*env)->GetObjectClass(env, instance);
    if (cls == NULL) {
        LOGE("can not find cls of Native07\n");
        return;
    }
    j_mid = (*env)->GetMethodID(env, cls, "onThreadCallback", "(I)V");
    if (j_mid == NULL) {
        LOGE("can not get onThreadCallback method id\n");
        return;
    }
    //充分证明了释放j_mid是会crash的,因此不需要释放jMethod类型的数据.
    //(*env)->DeleteLocalRef(env,j_mid);

    (*env)->DeleteLocalRef(env,cls);

    pthread_t threads[5] = {0};
    for (int i = 0; i < 5; i++) {
        pthread_create(&threads[i], NULL, (void *) threadFun, (void *) i);
    }

}


/**
 * 通过这个函数我们,将i的值返回给,java层的对象
 * @param i
 */
void threadFun(void *i) {

    //1.想要返回到java层,必须要一个JNIEnv*的对象.
    //javaVm 为每一个线程都会创建一个JNIEnv* 的对象,因此不同线程的JNIEnv* 各自独立的,不能相互使用
    // JavaVm的实例是唯一的.因此我们可以通过JavaVM获取该线程的JNIEnv对象.
    //那么JavaVM由如何获取呢?既然是唯一的,我们就可以全局保存获取.
    JNIEnv *env = NULL;
    int ret = -1;
    if ((ret = (*g_vm)->AttachCurrentThread(g_vm, &env, NULL)) < 0) {
        LOGE("attachCurrentThread failed\n");
        return;
    }
    assert(env != NULL);

    //使用全局的jMethodId,经过验证可以得到正确的结果
    //(*env)->CallVoidMethod(env, globalApi07Obj, j_mid, (int) i); //此处正确

    //这里我们还需要一个jClass对象
    jclass cls = (*env)->GetObjectClass(env, globalApi07Obj);
    if (cls == NULL) {
        LOGE("can not find cls of globalApi07Obj\n");
        return;
    }
    jmethodID j_mid2= (*env)->GetMethodID(env, cls, "onThreadCallback", "(I)V");
    if (j_mid == NULL) {
        LOGE("can not get onThreadCallback method02 id\n");
        return;
    }

    (*env)->DeleteLocalRef(env,cls);
    (*g_vm)->DetachCurrentThread(g_vm);
    //所有的env操作,要在DetachCurrentThread之前完成,因为DetachCurrentThread会接触线程关联,无法再使用env了.
   // (*env)->DeleteLocalRef(env,cls);  //此处操作错误


    pthread_exit(0);
}