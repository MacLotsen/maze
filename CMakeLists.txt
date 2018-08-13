cmake_minimum_required(VERSION 3.3)
project(cmaze)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c11 -Wall -lncurses")

enable_testing()

add_subdirectory(src)
