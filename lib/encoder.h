//
// Created by Artem Ustinov on 6/2/2018.
//

#ifndef HUFFMAN_ENCODER_H
#define HUFFMAN_ENCODER_H

#include "huffman_tree.h"
#include <vector>
#include "code.h"

class encoder : public huffman_tree {
public:
    void encode(std::vector<unsigned char> const &data, code &c_data) const;

    explicit encoder(frequency const &freq);
};


#endif //HUFFMAN_COMPRESSOR_H
