cmake_minimum_required(VERSION 3.9)
project(HUFFMAN_LIB)
include(gtest.cmake)
include_directories(${HUFFMAN_LIB_SOURCE_DIR})
set(CMAKE_CXX_STANDARD 17)

add_library(huff_lib huffman_tree.cpp huffman_tree.h
        code_word.cpp code_word.h
        frequency.cpp frequency.h
        encoder.cpp encoder.h
        code.cpp code.h
        decoder.cpp decoder.h)

add_executable(tests test.cpp)
find_package(Threads)

target_link_libraries(tests gtest ${CMAKE_THREAD_LIBS_INIT})

target_compile_options(tests PRIVATE -std=c++17 -O3)

target_link_libraries(tests huff_lib)