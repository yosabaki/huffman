cmake_minimum_required(VERSION 3.9)
project(HUFFMAN_SRC)
include_directories(${HUFFMAN_SRC_SOURCE_DIR})
include_directories(${HUFFMAN_LIB_SOURCE_DIR})
set(CMAKE_CXX_STANDARD 17)

add_executable(huffman
        main.cpp
        compressor.cpp
        compressor.h)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -O3")

target_link_libraries(huffman huff_lib)