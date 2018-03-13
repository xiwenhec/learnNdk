cmake_minimum_required(VERSION 3.4.1)

add_library(
        learnNdk
        SHARED
        lesson01.c
        lesson02.c
        lesson03.c
        lesson04.c
        lesson05.c
        lesson06.c
)


find_library(
        log-lib
        log)


target_link_libraries(
        learnNdk
        ${log-lib})