cmake_minimum_required(VERSION 3.22)
project(stl_iostreams)

set(CMAKE_CXX_STANDARD 23)

add_executable(associative_containers ../part_2_associative_containers/main.cpp Client.h ClientMap.h ClientMap.cpp Date.h Date.cpp Time.h Time.cpp)