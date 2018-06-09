//
// Created by artyo on 6/2/2018.
//

#include <cstring>
#include "frequency.h"

frequency::frequency() : freq(256, 0) {
    _size = 0;
}

unsigned int frequency::size() const {
    return _size;
}

frequency::frequency(std::vector<unsigned long long> const &f) {
    freq = f;
    _size = 0;
    for (int i = 0; i < 256; i++)
        _size += (freq[i] != 0);
}

void frequency::add_frequency(std::vector<unsigned char> const &stream) {
    for (auto c:stream)
        freq[c]++;
    _size = 0;
    for (int i = 0; i < 256; i++)
        _size += (freq[i] != 0);
}

unsigned long long &frequency::operator[](size_t _n) {
    return freq[_n];
}

const unsigned long long &frequency::operator[](size_t _n) const {
    return freq[_n];
}
