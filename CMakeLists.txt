cmake_minimum_required(VERSION 4.0)
project(MathRadical)

set(CMAKE_CXX_STANDARD 20)

add_executable(MathRadical main.cpp
        Math/MathUtils.cpp
        Math/MathUtils.h)
