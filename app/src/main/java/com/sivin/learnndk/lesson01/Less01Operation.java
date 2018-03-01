package com.sivin.learnndk.lesson01;

import com.sivin.learnndk.bean.Student;

public class Less01Operation {

    public void performClick(){
        NativeApi nativeApi = new NativeApi();
        nativeApi.accessField();
        nativeApi.accessPersonField(new Student("sivin",10));
    }
}
