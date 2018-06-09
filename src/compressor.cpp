//
// Created by Artem Ustinov on 6/2/2018.
//

#include <fstream>
#include <cstring>
#include "compressor.h"
#include "encoder.h"
#include "decoder.h"

const size_t READ_SIZE = 1 << 15;

unsigned long long h_d = 5381;

unsigned long long modernize(unsigned long long &h, const char *s, size_t n) {
    int c;
    for (size_t i = 0; i < n; i++, s++) {
        c = *s;
        h = ((h << 5) + h) + c;
    }
    return h;
}

unsigned long long hash(const char *s, size_t n) {
    unsigned long long res = 5381;
    return modernize(res, s, n);
}

template<typename T>
void read(T &dst, std::basic_ifstream<char> &is) {
    char t[sizeof(T)];
    is.read(t, sizeof(T));
    memcpy(&dst, t, sizeof(T));
}

template<typename T>
void write(T const &src, std::basic_ofstream<char> &os) {
    char t[sizeof(T)];
    memcpy(t, &src, sizeof(T));
    os.write(t, sizeof(T));
}

frequency get_frequency(std::string const &file) {
    frequency f;
    std::ifstream in(file, std::ofstream::binary);
    while (!in.eof()) {
        std::vector<unsigned char> data(READ_SIZE);
        in.read(reinterpret_cast<char *>(data.data()), READ_SIZE);
        data.resize(in.gcount());
        modernize(h_d, reinterpret_cast<char *>(data.data()), data.size());
        f.add_frequency(data);
    }
    in.close();
    return f;
}

void compress(std::string const &src, std::string const &dst) {
    std::ifstream in(src, std::ofstream::binary);
    if (in.fail())
        throw (std::runtime_error("Can't open " + src + "\n"));
    frequency f = get_frequency(src);
    encoder e(f);
    std::ofstream out(dst, std::ifstream::binary);
    write(f.size(), out);
    char str_freq[f.size() * 5];
    int j = 0;
    for (int i = 0; i < 256; i++) {
        if (f[i] != 0) {
            unsigned char c = i;
            str_freq[j * 5] = c;
            out.write(reinterpret_cast<char *>(&c), 1);
            memcpy(str_freq + j * 5 + 1, &f[i], 4);
            write(f[i], out);
            j++;
        }
    }
    unsigned long long h_f = hash(str_freq, f.size() * 5);
    write(h_f, out);
    write(h_d, out);
    std::vector<unsigned char> data(READ_SIZE);
    code carry_code;
    while (!in.eof()) {
        in.read(reinterpret_cast<char *>(data.data()), READ_SIZE);
        data.resize(in.gcount());
        code c = carry_code;
        e.encode(data, c);
        if (!in.eof()) {
            carry_code = code({c.back()}, c.pos());
            c.pop_back();
        }
        out.write(reinterpret_cast<char *>(c.data()), c.data_size());
    }
    in.close();
    out.close();
}


void decompress(std::string const &src, std::string const &dst) {
    unsigned long long h_d = 5381;
    std::ifstream in(src, std::ofstream::binary);
    if (in.fail())
        throw (std::runtime_error("Can't open " + src + ".\n"));
    unsigned char c;
    unsigned long long freq;
    unsigned int n;
    read(n, in);
    if (in.eof() || n > 256)
        throw (std::runtime_error("Invalid file type. Try to decompress another file.\n"));
    std::vector<unsigned long long> tmp(256, 0);
    char str_f[n * 5];
    for (unsigned int i = 0; i < n && !in.eof(); i++) {
        read(c, in);
        read(freq, in);
        memcpy(str_f + i * 5, &c, 1);
        memcpy(str_f + i * 5 + 1, &freq, 4);
        tmp[c] = freq;
    }
    if (in.eof())
        throw (std::runtime_error("Invalid file type. Try to decompress another file.\n"));
    unsigned long long h_f = hash(str_f, n * 5);
    unsigned long long cmp_h_f, cmp_h_d;
    read(cmp_h_f, in);
    read(cmp_h_d, in);
    if (h_f != cmp_h_f)
        throw (std::runtime_error("Invalid file type. Try to decompress another file.\n"));
    frequency f(tmp);
    decoder d(f);
    size_t size = d.get_count();
    std::ofstream out(dst, std::ifstream::binary);
    std::vector<unsigned char> data(READ_SIZE);
    while (!in.eof()) {
        in.read(reinterpret_cast<char *>(data.data()), READ_SIZE);
        data.resize(in.gcount());
        std::vector<unsigned char> tmp_data = d.decode_stream(code(data, std::min(size, data.size() * 8)));
        modernize(h_d, reinterpret_cast<char *>(tmp_data.data()), tmp_data.size());
        out.write(reinterpret_cast<char *>(tmp_data.data()), tmp_data.size());
        size -= std::min(data.size() * 8, size);
    }
    in.close();
    out.close();
    d.close_stream();
    if (h_d != cmp_h_d)
        throw (std::runtime_error("Invalid decompressed data. " + dst + " can become unusable.\n"));
}
