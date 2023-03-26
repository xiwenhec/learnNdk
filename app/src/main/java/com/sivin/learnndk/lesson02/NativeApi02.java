package com.sivin.learnndk.lesson02;

import android.util.Log;

import com.sivin.learnndk.bean.Course;

public class NativeApi02 {


    public native void changeValue(int a ,int b);
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


    /**
     * 这个函数将会把形如"30+20"的字符串计算出来
     * @param str
     */
    public native void calcuateStr(String str);

    /**
     * "(ILjava/lang/String;)V"
     * @param value
     * @param opter
     */
    public static void onNativeStaticCallback(int value ,String opter){
        Log.e("lesson02", "onNativeStaticCallback: "+value +" opter:"+opter);
    }


    public native void callStaticMedthod2();


    /**
     * 触发方法构造函数 同时返回一个java层的对象
     */
    public native Course callConstructMethd();



}
