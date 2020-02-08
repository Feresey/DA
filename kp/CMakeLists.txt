cmake_minimum_required(VERSION 3.0)
project(kursa4)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wpedantic")
set(CMAKE_CXX_FLAGS_RELEASE "-O2")
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g3")

add_subdirectory(src)

install(TARGETS kp RUNTIME DESTINATION)
