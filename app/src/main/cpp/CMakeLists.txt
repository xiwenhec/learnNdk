cmake_minimum_required(VERSION 3.4.1)

set(ANDROID_STL_TYPE c++_shared)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -fno-rtti -fno-exceptions -Wall")
add_library(
        learnNdk
        SHARED
        lesson01.c
        lesson02.c
        lesson03.c
        lesson04.c
        lesson05.c
        lesson06.c
        lesson07.c
        jni_register.c
        stllearn.cpp
)

find_library(
        log-lib
        log)


target_link_libraries(
        learnNdk
        ${log-lib})