//
// Created by Artem Ustinov on 6/2/2018.
//

#include "code.h"

code::code() : _data{0}, _pos(0), _size(0) {}

code::code(std::vector<unsigned char> const &d, size_t s) : _data(d), _pos(static_cast<unsigned char>(s % 8)),
                                                            _size(s) {}

void code::push_word(code_word const &w) {
    _size += w.length;
    unsigned char &t = _data.back();
    t &= (1 << _pos) - 1;
    t += w.word << _pos;
    _pos += w.length;
    int k = 1;
    while (_pos > 7) {
        _data.push_back(static_cast<unsigned char>(w.word >> (8 * k - ((_pos - w.length) % 8))));
        _pos -= 8;
        k++;
    }
}

size_t code::size() const {
    return _size;
}

unsigned int code::pos() const {
    return _pos;
}

void code::pop_back() {
    _data.pop_back();
    _size -= _pos;
    _pos = 0;
}

unsigned char &code::back() {
    return _data.back();
}

unsigned char &code::operator[](size_t _n) {
    return _data[_n];
}

unsigned char const &code::operator[](size_t _n) const {
    return _data[_n];
}

unsigned char *code::data() {
    return _data.data();
}

size_t code::data_size() {
    return _data.size();
}

