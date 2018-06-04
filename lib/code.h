//
// Created by Artem Ustinov on 6/2/2018.
//

#ifndef HUFFMAN_CODE_H
#define HUFFMAN_CODE_H

#include <vector>
#include <string>
#include "code_word.h"

struct code {

    code();

    code(std::vector<unsigned char> const &d, size_t s);

    void push_word(code_word const &w);

    size_t size() const;

    unsigned int pos() const;

    void pop_back();

    unsigned char &back();

    unsigned char &operator[](size_t _n);

    unsigned char const &operator[](size_t _n) const;

    unsigned char *data();

    size_t data_size();

private:
    std::vector<unsigned char> _data;
    size_t _size;
    unsigned int _pos;
};


#endif //HUFFMAN_CODE_H
