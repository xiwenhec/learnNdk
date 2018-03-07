package com.sivin.learnndk.lesson03;

import android.util.Log;

public class NativeApi03 {

    //在JNI层做快速排序
    public native void sortArray(int[] arr);

    /**
     * 从C/C++返回的字节数组
     * @param arr 字节数组
     */
    private void onDataCome(byte[] arr){
        String str = new String(arr);
        Log.d("lesson03", str);
    }


    public native void triggerDataCome();


}
