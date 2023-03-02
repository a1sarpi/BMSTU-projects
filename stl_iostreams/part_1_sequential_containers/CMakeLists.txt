cmake_minimum_required(VERSION 3.22)
project(stl_iostreams)

set(CMAKE_CXX_STANDARD 23)

add_executable(sequential_containers ../part_1_sequential_containers/main.cpp CreateData.cpp CreateData.h LoadData.h Modify.h OutputResult.h Application.h)