package com.sivin.learnndk.lesson02;

import android.util.Log;

public class NativeApi02 {

    /**
     * 从JNI回调的函数
     * @param a
     * @param b
     * @param value
     * "(IILjava/lang/String;)V"
     */
    private void onNativeCallback(int a , int b ,String value){
        Log.e("Lesson02", "onNativeCallback: a:"+a+" b："+b+" value:"+value);
    }

    public native void changeValue(int a ,int b);

}
