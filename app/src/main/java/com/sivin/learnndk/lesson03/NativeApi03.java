package com.sivin.learnndk.lesson03;

import android.util.Log;

import java.io.UnsupportedEncodingException;

public class NativeApi03 {

    //在JNI层做快速排序
    public native void sortArray(int[] arr);

    /**
     * 从C/C++返回的字节数组
     * @param arr 字节数组
     */
    public void onDataCome(byte[] arr){
        String str = null;
        try {
            str = new String(arr,"UTF-8");
        } catch (UnsupportedEncodingException e) {
            e.printStackTrace();
        }
        Log.d("lesson03", str);
    }

    public native void triggerData();


}
