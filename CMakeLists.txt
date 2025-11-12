cmake_minimum_required(VERSION 3.0.0)
project(AnalyzeLog VERSION 0.1.0 LANGUAGES C CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_C_FLAGS_DEBUG "-g")
set(CMAKE_BUILD_TYPE Debug)

add_executable(Sandpile main.cpp)
