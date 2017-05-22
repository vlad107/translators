cmake_minimum_required(VERSION 2.8)

project(cpp_generator)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -msse4.2 -ggdb -g -O0")

file(GLOB_RECURSE CPP_FILES    "./source/*.cpp")
file(GLOB_RECURSE H_FILES      "./include/*.h")

include_directories("include")

add_executable(${PROJECT_NAME} ${CPP_FILES} "main.cpp" ${H_FILES})
