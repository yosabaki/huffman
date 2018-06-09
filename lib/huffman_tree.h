//
// Created by Artem Ustinov on 6/1/2018.
//

#ifndef HUFFMAN_HUFFMAN_TREE_H
#define HUFFMAN_HUFFMAN_TREE_H

#include <vector>
#include <bitset>
#include <memory>

#include "code_word.h"
#include "frequency.h"

class huffman_tree {
public:
    explicit huffman_tree(frequency const &freq);

    unsigned get_count() const;

protected:

    std::vector<code_word> symbols;

    struct Node {
        size_t l, r, ind;
        unsigned char symbol;
        unsigned long long weight;

        Node() : l(0), r(0), ind(0), symbol(0), weight(UINT64_MAX) {}

        Node(unsigned long long w, unsigned char c, size_t i) : l(0), r(0), ind(i), symbol(c), weight(w) {}

        Node(unsigned long long w, size_t _l, size_t _r, size_t i) : l(_l), r(_r), ind(i), symbol(0), weight(w) {}
    };

    unsigned count;

    void set_symbols(size_t curr, code_word &curr_word);

    std::vector<Node> tree;

    size_t root;
};


#endif //HUFFMAN_HUFFMAN_TREE_H
