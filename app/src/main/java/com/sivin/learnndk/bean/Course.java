package com.sivin.learnndk.bean;

public class Course {
    //课程的名字
    private String mCureseName;
    //课程的分数
    private int mGrade;

    public Course(String mCureseName, int mGrade) {
        this.mCureseName = mCureseName;
        this.mGrade = mGrade;
    }

    public String getmCureseName() {
        return mCureseName;
    }

    public void setmCureseName(String mCureseName) {
        this.mCureseName = mCureseName;
    }

    public int getmGrade() {
        return mGrade;
    }

    public void setmGrade(int mGrade) {
        this.mGrade = mGrade;
    }
}
