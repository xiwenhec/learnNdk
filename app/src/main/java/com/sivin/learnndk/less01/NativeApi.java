package com.sivin.learnndk.less01;

public class NativeApi {
    private String key = "test";

    public String getKey(){
        return key;
    }

    //通过JNI获取java层的属性成员，这个方法我们获取的是当前类对象的属性成员
    public native void accessField();


    public native void accessField(Person person);
    public native void accessPersonField(Person person);
}
