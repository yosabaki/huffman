//
// Created by Artem Ustinov on 6/1/2018.
//

#include "code_word.h"

code_word::code_word() : word(0), length(0) {}

code_word::code_word(unsigned long long _word, unsigned int _length) : word(_word), length(_length) {}

void code_word::push_bit(bool b) {
    word += static_cast<unsigned long long> (b) << length;
    length++;
}

void code_word::pop_bit() {
    length--;
    word &= (1ull << length) - 1;
}