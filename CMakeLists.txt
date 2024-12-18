cmake_minimum_required(VERSION 3.10)

project(ENCLIPTICA)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_COMPILER /usr/local/bin/g++)

set(BOOST_ROOT "/usr/local/Cellar/boost/1.87.0")
include_directories(${BOOST_ROOT}/include)
include_directories(.)

add_executable(main main.cpp)