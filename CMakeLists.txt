cmake_minimum_required(VERSION 3.10)

set(PROJECT_NAME ThousandsBallot)
project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_COMPILER g++)
set(CMAKE_C_COMPILER gcc)

if(DEFINED ENV{BOOST_INCLUDE})
  set(BOOST_INCLUDE $ENV{BOOST_INCLUDE})
elseif()
  message(FATAL_ERROR "BOOST_INCLUDE is not set")
endif()

if(DEFINED ENV{BOOST_LIB})
  set(BOOST_LIB $ENV{BOOST_LIB})
elseif()
  message(FATAL_ERROR "BOOST_LIB is not set")
endif()

find_package(GTest REQUIRED)
include_directories(${BOOST_INCLUDE})
include_directories(${GTEST_INCLUDE_DIRS})
link_directories(${BOOST_LIB})
include_directories(/usr/local/include)
include_directories(./include)

option(NTT "Enable NTT" OFF)
option(NTT_DEBUG "Enable NTT Debug" OFF)

if(NTT)
  add_definitions(-DNTT)
  if (NTT_DEBUG)
    add_definitions(-DNTT_DEBUG)
  endif()
endif()


set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

set(SOURCE_FILES
    src/params/params.cpp
    src/params/nttparams.cpp
    src/operator/Montgomery.cpp
    src/structure/torus.cpp
    src/structure/galoisfield.cpp
    src/structure/toruspoly.cpp
    src/structure/intpoly.cpp
    src/structure/galoisfieldpoly.cpp
    src/strategy/ntt_multiplication_strategy.cpp
    src/strategy/naive_multiplication_strategy.cpp
    src/factory/multiplication_factory.cpp)

set(MAIN ThousandsBallot)
add_executable(${MAIN} main.cpp ${SOURCE_FILES})
target_link_libraries(${MAIN} -lboost_program_options)

# set(SERVER server)
# add_executable(${SERVER} network/server.cpp ${SOURCE_FILES})
# target_link_libraries(${SERVER} -lboost_program_options)

# set(CLIENT client)
# add_executable(${CLIENT} network/client.cpp ${SOURCE_FILES})
# target_link_libraries(${CLIENT} -lboost_program_options)

set(TEST_SOURCE_FILES
    src/test/test_montgomerymul.cpp
    src/params/params.cpp
    src/operator/Montgomery.cpp
    src/structure/torus.cpp
    src/structure/galoisfield.cpp)

add_executable(test_montgomerymul ${TEST_SOURCE_FILES})
target_link_libraries(test_montgomerymul ${GTEST_LIBRARIES} GTest::gtest_main pthread)

enable_testing()
add_test(NAME MontgomeryTest COMMAND test_montgomerymul --P=12289 --r=18 --seed=1)
add_test(NAME MontgomeryTest2 COMMAND test_montgomerymul --P=12289 --r=18 --seed=2)
add_test(NAME MontgomeryTest3 COMMAND test_montgomerymul --P=12289 --r=18 --seed=3)
add_test(NAME MontgomeryTest4 COMMAND test_montgomerymul --P=12289 --r=18 --seed=4)
add_test(NAME MontgomeryTest5 COMMAND test_montgomerymul --P=12289 --r=18 --seed=5)