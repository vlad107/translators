cmake_minimum_required(VERSION 2.8)

project(parser)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -msse4.2 -ggdb -g -O0")

file(GLOB_RECURSE CPP_FILES_PARSER "./gen/*.cpp")
file(GLOB_RECURSE H_FILES_PARSER   "./gen/*.h")

#message(${CPP_FILES_PARSER})

include_directories("gen")

add_executable(parser ${CPP_FILES_PARSER} "main.cpp" ${H_FILES_PARSER})
