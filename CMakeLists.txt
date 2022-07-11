cmake_minimum_required(VERSION 3.22)
project(MomentCalc)

set(CMAKE_CXX_STANDARD 14)

add_executable(MomentCalc
        main.cpp Matrix.cpp MomentMatrix.cpp)
