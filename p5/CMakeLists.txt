cmake_minimum_required(VERSION 3.5)
project(2017_p5)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES answer/calc.cpp answer/dlist.cpp)
add_executable(2017_p5_calc ${SOURCE_FILES})

set(SOURCE_FILES answer/call.cpp answer/dlist.cpp)
add_executable(2017_p5_call ${SOURCE_FILES})

set(SOURCE_FILES answer/test.cpp answer/dlist.cpp)
add_executable(2017_p5_test ${SOURCE_FILES})
