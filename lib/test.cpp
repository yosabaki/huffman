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
    for (int i = 0; i < 1e6; i++) {
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
    for (int i = 0; i < 28; i++) {
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

TEST(correctness, encode_stream_test) {
    const int N = 1e3, M = 256;
    std::vector<std::vector<unsigned char>> c(M);
    for (int j = 0; j < M; j++) {
        for (int i = 0; i < N; i++) {
            c[j].push_back(rand() % 256);
        }
    }
    frequency f;
    for (auto _c:c)
        f.add_frequency(_c);
    encoder e(f);
    decoder d(f);
    code code_tmp;
    for (auto _c:c) {
        e.encode(_c, code_tmp);
    }
    std::vector<unsigned char> ccc = d.decode(code_tmp);
    std::vector<unsigned char> cc(N * M);
    for (int j = 0; j < M; j++) {
        for (int i = 0; i < N; i++) {
            cc[j * N + i] = c[j][i];;
        }
    }
    EXPECT_EQ(cc, ccc);
}

TEST(correctness, decode_stream_test) {
    const int N = 1e3, M = 256;
    std::vector<std::vector<unsigned char>> c(M);
    for (int j = 0; j < M; j++) {
        for (int i = 0; i < N; i++) {
            c[j].push_back(rand() % 256);
        }
    }
    frequency f;
    for (auto _c:c)
        f.add_frequency(_c);
    encoder e(f);
    decoder d(f);
    std::vector<code> _code(M);
    for (int i = 0; i < M; i++) {
        e.encode(c[i], _code[i]);
    }
    std::vector<unsigned char> cc(N * M);
    for (int j = 0; j < M; j++) {
        for (int i = 0; i < N; i++) {
            cc[j * N + i] = c[j][i];;
        }
    }
    std::vector<unsigned char> ccc(N * M);
    int pos = 0;
    for (int i = 0; i < M; i++) {
        std::vector<unsigned char> tmp = d.decode_stream(_code[i]);
        for (int j = 0; j < tmp.size(); j++) {
            ccc[pos] = tmp[j];
            pos++;
        }
    }
    d.close_stream();
    EXPECT_EQ(cc, ccc);
}

TEST(correctness, decode_exception_test1) {
    std::vector<unsigned char> c;
    for (int i = 0; i < 1e3; i++) {
        c.push_back(rand() % 256);
    }
    frequency f;
    f.add_frequency(c);
    encoder e(f);
    decoder d(f);
    code code_tmp;
    e.encode(c, code_tmp);
    code_tmp.pop_back();
    EXPECT_ANY_THROW(d.decode(code_tmp));
}

TEST(correctness, decode_exception_test2) {
    std::vector<unsigned char> c;
    for (int i = 0; i < 100; i++) {
        c.push_back('a');
    }
    frequency f;
    f.add_frequency(c);
    encoder e(f);
    decoder d(f);
    code code_tmp;
    e.encode(c, code_tmp);
    code_tmp.push_word(code_word(0, 1));
    EXPECT_ANY_THROW(d.decode(code_tmp));
}