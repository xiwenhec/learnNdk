package com.sivin.learnndk.lesson04;

import android.util.Log;

public class Lesson04Operator {

    public void performClick(){

        NativeApi04 api = new NativeApi04();
        String a = api.initStr();
        Log.d("lesson04", "performClick: "+a );

    }



}
