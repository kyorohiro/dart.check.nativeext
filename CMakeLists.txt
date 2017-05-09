cmake_minimum_required(VERSION 3.8)
PROJECT(hello)

set(CMAKE_VERBOSE_MAKEFILE on)
include_directories(/usr/local/Cellar/dart/1.23.0/libexec)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -undefined dynamic_lookup")
set(CMAKE_VERBOSE_MAKEFILE on)
add_library(hello SHARED libhello.cpp)
