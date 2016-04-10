cmake_minimum_required(VERSION 3.3)
project(Compiler)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp lexer_t.cpp lexer_t.h token_t.h Node.cpp Node.h Parse.cpp Parse.h)
add_executable(Compiler ${SOURCE_FILES})