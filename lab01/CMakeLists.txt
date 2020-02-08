cmake_minimum_required(VERSION 3.0)

project(lab01 LANGUAGES CXX)

add_executable(lab01 main.cpp Sort.hpp)

add_executable(std_sort std_sort.cpp)

add_compile_options(-Wall -Wextra -Wpedantic -m32)

target_link_libraries(lab01 m)
target_link_libraries(std_sort m)
