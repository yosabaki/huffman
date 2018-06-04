cmake_minimum_required(VERSION 3.9)
project(HUFFMAN_LIB)
include_directories(${HUFFMAN_LIB_SOURCE_DIR})
set(CMAKE_CXX_STANDARD 17)

add_library(huff_lib huffman_tree.cpp huffman_tree.h
        code_word.cpp code_word.h
        frequency.cpp frequency.h
        encoder.cpp encoder.h
        code.cpp code.h
        decoder.cpp decoder.h)

add_executable(tests test.cpp
        gtest/gtest.h
        gtest/gtest_main.cc
        gtest/gtest-all.cc)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -O3 -fsanitize=address,undefined")

target_link_libraries(tests huff_lib)