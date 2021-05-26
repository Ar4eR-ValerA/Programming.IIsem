cmake_minimum_required(VERSION 3.19)
project(Lab_6)

set(CMAKE_CXX_STANDARD 17)

add_executable(Lab_6 main.cpp cube/cube.h cube/color.h cube/cube.cpp cube_algorithms.h cube_algorithms.cpp)