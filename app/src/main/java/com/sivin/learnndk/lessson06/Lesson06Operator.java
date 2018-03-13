package com.sivin.learnndk.lessson06;

import android.util.Log;

public class Lesson06Operator {

    public void performClick(){

        NativeApi06 api = new NativeApi06();
        String result = api.testDynamicRegister();
        Log.d("lesson06", result);
    }

}
