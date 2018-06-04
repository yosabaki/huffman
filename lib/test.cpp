#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <vector>
#include <utility>
#include <gtest/gtest.h>

#include "code.h"
#include "code_word.h"
#include "decoder.h"
#include "encoder.h"
#include "huffman_tree.h"

TEST(correctness, ab) {
    std::vector<unsigned char> c{'a', 'b'};
    frequency f;
    f.add_frequency(c);
    encoder e(f);
    decoder d(f);
    code code_tmp;
    e.encode(c, code_tmp);
    EXPECT_EQ(c, d.decode(code_tmp));
}

TEST(correctness, more_than_two_symbols) {
    std::vector<unsigned char> c;
    for (int i = 0; i < 100; i++) {
        c.push_back(rand() % 10);
    }
    frequency f;
    f.add_frequency(c);
    encoder e(f);
    decoder d(f);
    code code_tmp;
    e.encode(c, code_tmp);
    EXPECT_EQ(c, d.decode(code_tmp));
}

TEST(correctness, empty_data) {
    std::vector<unsigned char> c;
    frequency f;
    f.add_frequency(c);
    encoder e(f);
    decoder d(f);
    code code_tmp;
    e.encode(c, code_tmp);
    EXPECT_EQ(c, d.decode(code_tmp));
}

TEST(correctness, one_type_of_symbol) {
    std::vector<unsigned char> c;
    for (int i = 0; i < 1e5; i++) {
        c.push_back(0);
    }
    frequency f;
    f.add_frequency(c);
    encoder e(f);
    decoder d(f);
    code code_tmp;
    e.encode(c, code_tmp);
    EXPECT_EQ(c, d.decode(code_tmp));
}

TEST(correctness, big_data_random) {
    std::vector<unsigned char> c;
    for (int i = 0; i < 1e7; i++) {
        c.push_back(rand() % 256);
    }
    frequency f;
    f.add_frequency(c);
    encoder e(f);
    std::vector<unsigned long long> t(256);
    for (int i = 0; i < 256; i++) {
        t[i] = f[i];
    }
    f = frequency(t);
    decoder d(f);
    code code_tmp;
    e.encode(c, code_tmp);
    EXPECT_EQ(c, d.decode(code_tmp));
}

TEST(correctness, exponentional_test) {
    std::vector<unsigned char> c;
    int a = 1, b = 1;
    for (int i = 0; i < 34; i++) {
        for (int j = 0; j < a; j++) {
            c.push_back(i);
        }
        int t = a;
        a = a + b;
        b = t;
    }
    frequency f;
    f.add_frequency(c);
    encoder e(f);
    std::vector<unsigned long long> t(256);
    for (int i = 0; i < 256; i++) {
        t[i] = f[i];
    }
    f = frequency(t);
    decoder d(f);
    code code_tmp;
    e.encode(c, code_tmp);
    EXPECT_EQ(c, d.decode(code_tmp));
}