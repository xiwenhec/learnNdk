package com.sivin.learnndk.lesson05;

import android.util.Log;

public class Lesson05Operator {

    public void performClick(){

        NativeApi05 api = new NativeApi05();

        try {
            api.jniCreateException();
        }catch (Exception e){
            Log.e("lesson05", "performClick: "+e.toString() );
        }

    }



}
