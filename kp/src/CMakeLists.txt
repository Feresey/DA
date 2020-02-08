cmake_minimum_required(VERSION 3.0)

project(kp LANGUAGES CXX)

add_executable(${PROJECT_NAME}
               main.cpp
               core/Shazam.hpp
               simple/SimpleVector.hpp
               threads/Threads.hpp)

include_directories(BEFORE
                    core
                    shazam
                    complex
                    simple
                    threads)

add_subdirectory(simple)
add_subdirectory(core)

target_link_libraries(${PROJECT_NAME}
                      m
                      mpg123
                      pthread
                      shazam)
