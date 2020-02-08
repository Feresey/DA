cmake_minimum_required(VERSION 3.0)

project(lab06 LANGUAGES CXX)

add_executable(${PROJECT_NAME}
	main.cpp
	BigInt.cpp
	BigInt.hpp
	)

target_link_libraries(${PROJECT_NAME} m)
