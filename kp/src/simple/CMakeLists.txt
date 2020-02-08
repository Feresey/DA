cmake_minimum_required(VERSION 3.0)

project(simple_vector LANGUAGES CXX)

add_library(${PROJECT_NAME} STATIC SimpleVector.cpp SimpleVector.hpp)
