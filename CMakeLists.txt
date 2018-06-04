cmake_minimum_required(VERSION 3.9)
project(huffman)

include_directories(${huffman_SOURCE_DIR})
set(CMAKE_CXX_STANDARD 17)

add_subdirectory(lib)
add_subdirectory(src)