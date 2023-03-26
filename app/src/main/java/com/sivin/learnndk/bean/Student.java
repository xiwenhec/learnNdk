package com.sivin.learnndk.bean;

public class Student {
    private String name;
    private int age;
    private Course mCurse;

    public Student(String name , int age){
        this.name = name;
        this.age = age;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public int getAge() {
        return age;
    }

    public void setAge(int age) {
        this.age = age;
    }

    public Course getCurse() {
        return mCurse;
    }

    public void setCurse(Course mCurse) {
        this.mCurse = mCurse;
    }
}
