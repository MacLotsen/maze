cmake_minimum_required(VERSION 3.3)
project(disjoint_set)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp disjoint.h disjoint.cpp maze.h maze.cpp test.cpp test.h)
add_executable(disjoint_set ${SOURCE_FILES})