cmake_minimum_required(VERSION 3.10)

set(PROJECT_NAME ThousandsBallot)
project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_COMPILER /usr/local/bin/g++)
set(CMAKE_C_COMPILER /usr/local/bin/gcc)

set(BOOST_ROOT "/usr/local/boost_1_87_0")
find_package(GTest REQUIRED)
include_directories(/usr/local/include)
include_directories(${BOOST_ROOT})
include_directories(.)
link_directories(${BOOST_ROOT}/stage/gcc/lib)

add_executable(${PROJECT_NAME} main.cpp src/params/params.cpp)
add_executable(test_montgomerymul src/test/test_montgomerymul.cpp src/params/params.cpp)

target_link_libraries(${PROJECT_NAME} -lboost_program_options)
target_link_libraries(test_montgomerymul ${GTEST_LIBRARIES} GTest::gtest_main pthread)

enable_testing()
add_test(NAME MontgomeryTest COMMAND test_montgomerymul --P=12289 --r=18)