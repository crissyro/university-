cmake_minimum_required(VERSION 3.26)
project(university C)

set(CMAKE_C_STANDARD 11)

add_executable(university main.c
        main.c)
add_subdirectory(libs)
target_link_libraries(university data_structures)
target_link_libraries(university algorithms)
target_link_libraries(university  string_)


add_executable(work_with_files work_with_files.c)
add_executable(test_file_work.c test_file_work.c)