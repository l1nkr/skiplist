cmake_minimum_required(VERSION 3.10)

project(skiplist)

SET(CMAKE_BUILD_TYPE "Debug")
SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g")

add_executable(skiplist main.cpp)