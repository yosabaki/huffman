//
// Created by Artem Ustinov on 6/2/2018.
//

#ifndef HUFFMAN_FREQUENCY_H
#define HUFFMAN_FREQUENCY_H

#include <vector>

struct frequency {
    frequency();

    frequency(std::vector<unsigned long long> const &f);

    frequency(frequency const &other);

    void add_frequency(std::vector<unsigned char> const &stream);

    frequency &operator=(frequency const &other);

    ~frequency();

    unsigned int size() const;

    unsigned long long &operator[](size_t _n);

    unsigned long long &operator[](size_t _n) const;

private:
    unsigned long long *freq;
    
    unsigned int _size;
};


#endif //HUFFMAN_FREQUENCY_H
