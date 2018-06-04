//
// Created by artyo on 6/2/2018.
//

#include <cstring>
#include "frequency.h"

frequency::frequency() {
    freq = new unsigned long long[256];
    memset(freq, 0, 256 * 8);
    _size = 0;
}

unsigned int frequency::size() const {
    return _size;
}

frequency::frequency(std::vector<unsigned long long> const &f) {
    freq = new unsigned long long[256];
    memcpy(freq, f.data(), 256 * 8);
    _size = 0;
    for (int i = 0; i < 256; i++)
        _size += (freq[i] != 0);
}

frequency &frequency::operator=(frequency const &other) {
    delete[]freq;
    freq = new unsigned long long[256];
    memcpy(freq, other.freq, 256 * 8);
    _size = other._size;
    return *this;
}

frequency::frequency(frequency const &other) : _size(other._size) {
    freq = new unsigned long long[256];
    memcpy(freq, other.freq, sizeof(freq));
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

unsigned long long &frequency::operator[](size_t _n) const {
    return freq[_n];
}

frequency::~frequency() {
    delete[]freq;
}
