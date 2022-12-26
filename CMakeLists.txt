cmake_minimum_required(VERSION 3.23)
project(calculator)

set(CMAKE_CXX_STANDARD 23)

add_executable(calculator main.cpp header.h InfToRPN.cpp RPNtoAns.cpp)
