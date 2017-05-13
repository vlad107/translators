cmake_minimum_required(VERSION 2.8)

project(cpp_generator)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -msse4.2 -ggdb -g -O0")

add_executable(${PROJECT_NAME} "helper.cpp" "helper.h" "main.cpp")
