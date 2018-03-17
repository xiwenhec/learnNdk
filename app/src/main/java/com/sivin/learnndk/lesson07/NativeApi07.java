package com.sivin.learnndk.lesson07;

import android.util.Log;

public class NativeApi07 {

    private static final String TAG = "NativeApi07";


    public native void createThread();



    private void onThreadCallback(){
        Log.e(TAG, "onThreadCallback: "+Thread.currentThread().getName());
    }




}
