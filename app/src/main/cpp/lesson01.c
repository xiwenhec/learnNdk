/**
 *
 * 本节我们主要是针对jni如何访问java中的对象，获取java的native方法传递过来的值
 *
 */
#include <string.h>
#include "common.h"


//通过JNI获取java层的属性成员，这个方法我们获取的是当前类对象的属性成员
JNIEXPORT void JNICALL
Java_com_sivin_learnndk_lesson01_NativeApi_accessField(JNIEnv *env, jobject instance) {

    //1.获取这个对象的jclass对象
    jclass jclz = (*env)->GetObjectClass(env, instance);

    //2.获取这个类对象中的这个成员id (jFileId)
    jfieldID jfId = (*env)->GetFieldID(env, jclz, "key", "Ljava/lang/String;");

    //3.获取这个对象属性的值,我们知道key是一个String类型的成员，因此我们用jstring来接收.
    //jstring 对象数据JNI层数据类型,不能被C/C++层直接使用,需要进一步的处理为C/C++可用的数据类型
    jstring jstr = (*env)->GetObjectField(env, instance, jfId);

    //4.处理jstring
    jboolean isCopy = JNI_FALSE;
    //获取和释放应该是成对出现的,这里如果是copy的方式，这个值将会被赋值为1，否则是0，但是我们一般不关注这个是复制还是指针的指向
    //因此我们一般写的时候是给NULL,这里我们接受一下可以看看。
    const char *c_str = (*env)->GetStringUTFChars(env, jstr, &isCopy);
    //我们打印一下从java层获取的字符串数据
    LOGD("lesson01->accessField:%s", c_str);

    //5.释放零时分配的内存空间，记住，我们最好不要改变c_str的指针指向.
    (*env)->ReleaseStringUTFChars(env, jstr, c_str);
}

//这个函数的目的是让我们看到JNI层函数在遇到java的方法重载时,会具有怎样的函数对应
//我们应该尽量避免函数重载在JNI层的实现,因为android对JNI的标准并不是很完善
JNIEXPORT void JNICALL
Java_com_sivin_learnndk_lesson01_NativeApi_accessField__Lcom_sivin_learnndk_bean_Student_2(
        JNIEnv *env, jobject instance, jobject student) {
    // TODO
}




//本函数获取的是函数传入的student对象的成员属性
JNIEXPORT void JNICALL
Java_com_sivin_learnndk_lesson01_NativeApi_accessPersonField(JNIEnv *env, jobject instance,
                                                             jobject student) {
    //1. 获取jclss对象,这里我们传入的是person
    jclass jclz = (*env)->GetObjectClass(env, student);

    //2.获取fieldId,这里我们获取传入person对象的age,第三个参数传入的是field的名称，第四个参数传入的是field的签名
    jfieldID jfId = (*env)->GetFieldID(env, jclz, "age", "I");

    //3.获取这个field，我们知道它在java层是一个int类型的数据，因此转换到JNI层就编程了jint类型
    //因此我们使用的函数就是GetIntField函数,对应的还有其他的函数形如GetxxxField
    jint age = (*env)->GetIntField(env, student, jfId);

    //我们打印一下这个值看看是不是正确的值
    LOGD("lesson01->accessPersonField: age:%d", age);
    //注意：这里获取的值是jint类型的属于基本数据类型，虚拟机会自己管理内存空间,不需要我们做释放内存操作
}


//本次我们使用比较推荐的函数来处理字符串
JNIEXPORT void JNICALL
Java_com_sivin_learnndk_lesson01_NativeApi_accessPersonNameField(JNIEnv *env, jobject instance,
                                                                 jobject person) {
    //1. 获取jclss对象,这里我们传入的是person
    jclass jclz = (*env)->GetObjectClass(env, person);

    //2.获取fieldId,这里我们获取传入person对象的age,第三个参数传入的是field的名称，第四个参数传入的是field的签名
    jfieldID jfId = (*env)->GetFieldID(env, jclz, "name", "Ljava/lang/String;");

    //3.获取这个对象的对应属性的值，我们知道key是一个String类型的成员，因此我们用jstring来接收
    jstring jstr = (*env)->GetObjectField(env, instance, jfId);

    //我们使用第二种推荐的方式来将jstring->char*

    //首先我们定义一个字符串数组,我们假定认为字符串最大是不超过1024的,我们最好初始化一下这个数组
    char outBuf[1024] = {0};
    int len = (*env)->GetStringUTFLength(env, jstr);
    (*env)->GetStringUTFRegion(env, jstr, 0, len, outBuf);
    //与GetStringUTFChars相比，这个方法的功能是一样的，但是GetStringUTFRegion这个函数没有做任何的内存空间的分配
    //因此就没有对应的释放内存的函数。
    // GetStringUTFRegion这个函数会做越界检查，如果必要的话，会抛出异常StringIndexOutOfBoundsException

}


/*
 * 该函数获取的是静态数据成员,应该注意区分和非静态成员的不同,
 * 静态成员不属于某个对象,而属于整个类
 */
JNIEXPORT void JNICALL
Java_com_sivin_learnndk_lesson01_NativeApi_accessStaticField(JNIEnv *env, jobject instance) {
    //1. 获取jclss对象,这里我们传入的是person
    jclass jclz = (*env)->GetObjectClass(env, instance);

    //2.获取这个类对象中的这个成员id (jFileId)
    jfieldID jfId = (*env)->GetStaticFieldID(env, jclz, "keyStatic", "Ljava/lang/String;");

    //3.获取静态成员数据
    jstring jstr = (*env)->GetStaticObjectField(env, jclz, jfId);

    //4.剩下的处理就一样了
    char outBuf[1024] = {0};
    int len = (*env)->GetStringUTFLength(env, jstr);
    (*env)->GetStringUTFRegion(env, jstr, 0, len, outBuf);
    //我们看到static的函数加上了static的标识符，因此我们使用对应的方法时要分清这个调用
    //是属于static的还是属于instance的。

}


/**
 * 这个案例,我们做深一些,我获取student对象中course对象的name属性.
 * 然后将这个属性值作为函数的返回
 */
JNIEXPORT jstring JNICALL
Java_com_sivin_learnndk_lesson01_NativeApi_getStudentCurseName(JNIEnv *env, jobject instance,
                                                               jobject student) {
    //1.获取jclss
    jclass jStudentClz = (*env)->GetObjectClass(env, student);
    //2.获取fieldId
    jfieldID jStudentFieldId = (*env)->GetFieldID(env, jStudentClz, "mCurse",
                                                  "Lcom/sivin/learnndk/bean/Course;");
    //3.获取field
    jobject jCourse = (*env)->GetObjectField(env, student, jStudentFieldId);
    //4获取 course field jclass
    jclass jCourseClz = (*env)->GetObjectClass(env, jCourse);
    //4.获取course name fileId
    jfieldID jCureseNameFileId = (*env)->GetFieldID(env, jCourseClz, "mCureseName",
                                                    "Ljava/lang/String;");

    //5.获取jstring value
    jstring jCourseName = (*env)->GetObjectField(env, jCourse, jCureseNameFileId);

    char value[512];
    //C++中内置类型的栈变量，如果不手动初始化，则其值是随机的
    memset(value, 0, sizeof(value));

    int len = (*env)->GetStringUTFLength(env, jCourseName);
    (*env)->GetStringUTFRegion(env, jCourseName, 0, len, value);

    //这里我们创建jstring对象,当函数返回时,这个jstring对象就交给java虚拟机自己管理了,因此这里我们不用对内存做管理
    return (*env)->NewStringUTF(env, value);
}

