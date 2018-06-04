//
// Created by Artem Ustinov on 6/2/2018.
//

#ifndef HUFFMAN_DECODER_H
#define HUFFMAN_DECODER_H


#include "huffman_tree.h"
#include "code.h"

class decoder : public huffman_tree {
public:
    std::vector<unsigned char> decode(code const &data);

    std::vector<unsigned char> decode_stream(code const &data);

    decoder(frequency const &freq);

private:
    Node *scan;

    unsigned char get_symbol(int &ind, int &pos, code const &data);
};


#endif //HUFFMAN_DECODER_H
