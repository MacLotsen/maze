cmake_minimum_required(VERSION 3.3)
project(cmaze)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c11 -Wall")

find_package(Curses)

message(${CURSES_LIBRARIES})

include_directories(${CURSES_INCLUDE_DIR})

enable_testing()

add_subdirectory(src)
