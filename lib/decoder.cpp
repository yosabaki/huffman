//
// Created by Artem Ustinov on 6/2/2018.
//

#include <stdexcept>
#include "decoder.h"

decoder::decoder(frequency const &freq) : huffman_tree(freq), scan(root) {
}

std::vector<unsigned char> decoder::decode(code const &data) {
    std::vector<unsigned char> dec_data;
    int ind = 0, pos = 0;
    while (ind * 8 + pos < data.size()) {
        dec_data.push_back(get_symbol(ind, pos, data));
    }
    if (scan != root)
        throw std::runtime_error("Unexpected symbols at the end of encoded data");
    return dec_data;
}

std::vector<unsigned char> decoder::decode_stream(code const &data) {
    std::vector<unsigned char> dec_data;
    int ind = 0, pos = 0;
    while (ind * 8 + pos < data.size()) {
        dec_data.push_back(get_symbol(ind, pos, data));
    }
    if (scan != root)
        dec_data.pop_back();
    return dec_data;
}

void decoder::close_stream() {
    if (scan != root)
        throw std::runtime_error("Unexpected symbols at the end of encoded data");
}

unsigned char decoder::get_symbol(int &ind, int &pos, code const &data) {
    for (ind; ind * 8 + pos < data.size(); ind++) {
        for (pos; pos < 8; pos++) {
            auto curr_bit = static_cast<bool>(data[ind] & (1ull << pos));
            scan = (curr_bit ? tree[scan].l : tree[scan].r);
            if (scan == 0) {
                throw (std::runtime_error("Invalid data."));
            }
            if (tree[scan].l == 0) {
                pos++;
                unsigned char tmp = tree[scan].symbol;
                scan = root;
                return tmp;
            }
        }
        pos = 0;
    }
}
