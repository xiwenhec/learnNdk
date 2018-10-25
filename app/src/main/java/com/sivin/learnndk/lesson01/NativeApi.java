package com.sivin.learnndk.lesson01;

import com.sivin.learnndk.bean.Student;

public class NativeApi {

    private static String keyStatic = "test static";

    private String key = "test";

    public String getKey(){
        return key;
    }
    //通过JNI获取java层的属性成员，这个方法我们获取的是当前类对象的属性成员
    public native void accessField();
    //这个方法的定义是为了让我们看到java层的重载函数,在JNI层会有怎样的表现
    public native void accessField(Student student);



    public native void accessPersonField(Student student);
    public native void accessPersonNameField(Student student);

    public native String getStudentCurseName(Student student);

    //获取static数据成员
    public native void accessStaticField();
}
