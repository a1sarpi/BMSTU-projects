cmake_minimum_required(VERSION 3.22)
project(fe_mesh_loader)

set(CMAKE_CXX_STANDARD 23)

add_executable(meshloader AneuMeshLoader.cpp AneuMeshLoader.h MeshLoader.cpp MeshLoader.h Structures.h main.cpp)