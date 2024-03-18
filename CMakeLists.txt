cmake_minimum_required(VERSION 3.26)
project(university C)

set(CMAKE_C_STANDARD 11)

add_executable(university main.c
        main.c)
add_subdirectory(libs)
target_link_libraries(university data_structures)
target_link_libraries(university algorithms)
target_link_libraries(university  string_)


