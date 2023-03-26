package com.sivin.learnndk.lesson01;

import android.util.Log;

import com.sivin.learnndk.bean.Course;
import com.sivin.learnndk.bean.Student;
import com.sivin.learnndk.utils.MemoryUtil;

public class Lesson01Operator {

    public void performClick() {
        NativeApi nativeApi = new NativeApi();
        nativeApi.accessField();
        nativeApi.accessPersonField(new Student("sivin", 10));
        Student student = new Student("xiao ming", 18);
        student.setCurse(new Course("chinese", 100));
        String name = nativeApi.getStudentCurseName(student);
        Log.e("lesson01", "performClick: " + name);

        long amemory = MemoryUtil.getAvailableMemeory();
        Log.e("lesson01", "performClick:amemory= " + amemory / (1024 * 1024));
    }
}
