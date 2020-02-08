cmake_minimum_required(VERSION 3.0)

project(shazam LANGUAGES CXX)

add_library(${PROJECT_NAME} STATIC Shazam.hpp Shazam.cpp)

target_link_libraries(${PROJECT_NAME} simple_vector)
