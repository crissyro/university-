cmake_minimum_required(VERSION 3.26)
project(untitled C)

set(CMAKE_C_STANDARD 11)

add_executable(untitled main.c)
add_executable(10res 10res.c)
add_executable(work work.c)
add_executable(12lab 12lab.c)

add_subdirectory(libs)
target_link_libraries(untitled data_structures)
target_link_libraries(untitled algorithms)
