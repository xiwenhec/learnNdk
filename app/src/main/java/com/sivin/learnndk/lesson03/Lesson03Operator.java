package com.sivin.learnndk.lesson03;

import android.util.Log;

public class Lesson03Operator {

    public void performClick(){
        NativeApi03 nativeApi = new NativeApi03();
        int arr[] = {5,7,6,8,2};
        nativeApi.sortArray(arr);
        for(int i : arr){
            Log.d("lesson03", "performClick: "+i);
        }
    }


}
