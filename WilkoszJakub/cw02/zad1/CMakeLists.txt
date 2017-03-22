cmake_minimum_required (VERSION 2.6)
project (sysop_1)
set(CMAKE_C_FLAGS "-g -std=c99")
#version num
set (sysop_1_VERSION_MAJOR 1)
set (sysop_1_VERSION_MINOR 0)



add_executable (sysop_2 rw.c)


add_custom_target(run sysop_2 test > wyniki.txt)
