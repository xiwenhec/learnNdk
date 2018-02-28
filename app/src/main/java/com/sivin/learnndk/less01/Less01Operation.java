package com.sivin.learnndk.less01;

public class Less01Operation {

    public void performClick(){
        NativeApi nativeApi = new NativeApi();
        nativeApi.accessField();
        nativeApi.accessPersonField(new Person("sivin",10));
    }
}
