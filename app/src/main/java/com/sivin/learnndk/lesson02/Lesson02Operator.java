package com.sivin.learnndk.lesson02;

import android.util.Log;

import com.sivin.learnndk.bean.Course;

public class Lesson02Operator {

    public void performClick(){
        NativeApi02 api = new NativeApi02();
        //api.changeValue(10,20);
        //api.calcuateStr("123+456");
        Course course = api.callConstructMethd();

        if(course != null){
            Log.d("LessonOpertor02", "get course name from JNI "+course.getmCureseName());
        }

    }


}
