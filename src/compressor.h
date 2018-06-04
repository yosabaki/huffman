//
// Created by Artem Ustinov on 6/2/2018.
//

#ifndef HUFFMAN_COMPRESSOR_H
#define HUFFMAN_COMPRESSOR_H

#include <string>

void compress(std::string const &src, std::string const &dst);

void decompress(std::string const &src, std::string const &dst);

#endif //HUFFMAN_COMPRESSOR_H
