cmake_minimum_required(VERSION 3.4)
project(DataStructures)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES hashmap.h hashmap.c dynamiclist.h dynamiclist.c testmain.c)
add_executable(DataStructures ${SOURCE_FILES})