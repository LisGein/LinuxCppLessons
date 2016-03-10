cmake_minimum_required(VERSION 3.3)
project(test_compiler)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

set(SOURCE_FILES main.cpp ../Compiler/lexer_t.cpp)
add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(test_compiler ${GTEST_LIBRARIES} pthread)