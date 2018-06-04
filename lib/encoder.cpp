//
// Created by Artem Ustinov on 6/2/2018.
//

#include "encoder.h"

encoder::encoder(frequency const &freq) : huffman_tree(freq) {}

void encoder::encode(std::vector<unsigned char> const &data, code &c_data) const {
    for (auto c:data) {
        c_data.push_word(symbols[c]);
    }
}