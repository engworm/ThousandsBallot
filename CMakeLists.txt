cmake_minimum_required(VERSION 3.10)

set(PROJECT_NAME Encliptica)
project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_COMPILER /usr/local/bin/g++)

set(BOOST_ROOT "/usr/local/boost_1_87_0")
include_directories(/usr/local/include)
include_directories(${BOOST_ROOT})
include_directories(.)
link_directories(${BOOST_ROOT}/stage/gcc/lib)

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} -lboost_program_options)