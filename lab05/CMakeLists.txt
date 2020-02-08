cmake_minimum_required(VERSION 3.0.0)
project(lab05 VERSION 0.1.0)

include(CTest)
enable_testing()
add_compile_options("-pedantic" "-Wall" "-Wextra" "-Wpedantic" "-Wno-sign-compare" "-g3" "-Wold-style-cast" "-Wconversion" "-Wsign-conversion" "-Wunreachable-code" "-Wno-comment")
add_executable(lab05 main.cpp TSuffixTree.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
