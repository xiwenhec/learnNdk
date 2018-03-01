#include <jni.h>
#include <android/log.h>
#define TAG "NDK"
#define LOGV(...) __android_log_print(ANDROID_LOG_VERBOSE, TAG, __VA_ARGS__)
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, TAG, __VA_ARGS__)
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, TAG, __VA_ARGS__)
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN, TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, TAG, __VA_ARGS__)

//通过JNI获取java层的属性成员，这个方法我们获取的是当前类对象的属性成员
JNIEXPORT void JNICALL
Java_com_sivin_learnndk_less01_NativeApi_accessField(JNIEnv *env, jobject instance) {

    //1.获取这个对象的jclass对象
    jclass jclz = (*env)->GetObjectClass(env,instance);

    //2.获取这个类对象中的这个成员id (jFileId)
    jfieldID jfId = (*env)->GetFieldID(env,jclz,"key","Ljava/lang/String;");

    //3.获取这个对象的对应属性的值，我们知道key是一个String类型的成员，因此我们用jstring来接收
    jstring jstr = (*env)->GetObjectField(env,instance,jfId);

    //4.处理jstring
    jboolean isCopy = JNI_FALSE;
    //获取和释放应该是成对出现的,这里如果是copy的方式，这个值将会被赋值为1，否则是0，但是我们一般不关注这个是复制还是指针的指向
    //因此我们一般写的时候是给NULL,这里我们接受一下可以看看。
    const char *c_str = (*env)->GetStringUTFChars(env,jstr,&isCopy);
    //我们打印一下从java层获取的字符串数据
    LOGD("%s",c_str);

    //5.释放零时分配的内存空间，记住，我们最好不要改变c_str的指针指向
    (*env)->ReleaseStringUTFChars(env,jstr,c_str);
}

//这个方法获取的是java层person对象的属性成员，我们同时也看到了java层的方法重载映射到JNI层的函数名称的变化是
JNIEXPORT void JNICALL
Java_com_sivin_learnndk_less01_NativeApi_accessField__Lcom_sivin_learnndk_less01_Person_2(
        JNIEnv *env, jobject instance, jobject person) {


    // TODO
}
//这里我们生成多个函数进行对比，下面我实现其中的一个，我们最好不要使用函数重载来实现，因为android对JNI的标准并不是很完善
JNIEXPORT void JNICALL
Java_com_sivin_learnndk_less01_NativeApi_accessPersonField(JNIEnv *env, jobject instance,
                                                           jobject person) {
    //1. 获取jclss对象,这里我们传入的是person
    jclass jclz = (*env)->GetObjectClass(env,person);

    //2.获取fieldId,这里我们获取传入person对象的age,第三个参数传入的是field的名称，第四个参数传入的是field的签名
    jfieldID jfId = (*env)->GetFieldID(env,jclz,"age","I");

    //3.获取这个field，我们知道他在java层是一个int类型的数据，因此转换到JNI层就编程了jint类型
    //因此我们使用的函数就是GetIntField函数
    jint age = (*env)->GetIntField(env,person,jfId);

    //我们打印一下这个值看看是不是正确的值
    LOGD("age:%d",age);
    //注意：这里获取的值是jint类型的属于基本数据类型，虚拟机会自己管理内存空间
}


//本次我们使用比较推荐的函数来处理字符串
JNIEXPORT void JNICALL
Java_com_sivin_learnndk_less01_NativeApi_accessPersonNameField(JNIEnv *env, jobject instance,
                                                               jobject person) {
    //1. 获取jclss对象,这里我们传入的是person
    jclass jclz = (*env)->GetObjectClass(env,person);

    //2.获取fieldId,这里我们获取传入person对象的age,第三个参数传入的是field的名称，第四个参数传入的是field的签名
    jfieldID jfId = (*env)->GetFieldID(env,jclz,"name","Ljava/lang/String;");

    //3.获取这个对象的对应属性的值，我们知道key是一个String类型的成员，因此我们用jstring来接收
    jstring jstr = (*env)->GetObjectField(env,instance,jfId);

    //我们使用第二种推荐的方式来讲jstring->char*

    //首先我们定义一个字符串数组,我们假定认为字符串最大是不超过1024的
    char outBuf[1024];
    int len = (*env)->GetStringUTFLength(env,jstr);
    (*env)->GetStringUTFRegion(env,jstr,0,len,outBuf);
    //与GetStringUTFChars相比，这个方法的功能是一样的，但是GetStringUTFRegion这个函数没有做任何的内存空间的分配
    //因此就没有对应的释放内存的函数了。
    // GetStringUTFRegion这个函数会做越界检查，如果必要的话，会抛出异常StringIndexOutOfBoundsException

}

JNIEXPORT void JNICALL
Java_com_sivin_learnndk_less01_NativeApi_accessStaticField(JNIEnv *env, jobject instance) {
    //1. 获取jclss对象,这里我们传入的是person
    jclass jclz = (*env)->GetObjectClass(env,instance);

    //2.获取这个类对象中的这个成员id (jFileId)
    jfieldID jfId = (*env)->GetStaticFieldID(env,jclz,"keyStatic","Ljava/lang/String;");

    //3.获取静态成员数据
    jstring jstr = (*env)->GetStaticObjectField(env,jclz,jfId);

    //4.剩下的处理就一样了
    char outBuf[1024];
    int len = (*env)->GetStringUTFLength(env,jstr);
    (*env)->GetStringUTFRegion(env,jstr,0,len,outBuf);

    //我们看到static的函数加上了static的标识符，因此我们使用对应的方法时要分清这个调用
    //是属于static的还是属于instance的。

}