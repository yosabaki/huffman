//
// Created by Artem Ustinov on 6/1/2018.
//

#ifndef HUFFMAN_CODE_WORD_H
#define HUFFMAN_CODE_WORD_H


struct code_word {
    code_word();

    code_word(code_word const &other) = default;

    code_word(unsigned long long _word, unsigned int _length);

    void push_bit(bool b);

    void pop_bit();

    unsigned long long word;
    unsigned int length;

};


#endif //HUFFMAN_CODE_WORD_H
