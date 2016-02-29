cmake_minimum_required(VERSION 3.3)
project(tema0)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)
set(HEADER_FILES utils.h)
add_executable(tema0 ${SOURCE_FILES} ${HEADER_FILES})
