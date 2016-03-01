cmake_minimum_required(VERSION 3.3)
project(tema1)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(HEADER_FILES utils.h)
set(SOURCE_FILES main.cpp)
add_executable(tema1 ${HEADER_FILES} ${SOURCE_FILES})