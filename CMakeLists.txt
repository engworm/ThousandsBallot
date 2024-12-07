cmake_minimum_required(VERSION 3.10)

project(ENCLIPTICA VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_COMPILER /usr/local/bin/g++)

add_executable(main main.cpp)