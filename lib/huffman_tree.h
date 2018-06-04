//
// Created by Artem Ustinov on 6/1/2018.
//

#ifndef HUFFMAN_HUFFMAN_TREE_H
#define HUFFMAN_HUFFMAN_TREE_H

#include <vector>
#include <bitset>
#include "code_word.h"
#include "frequency.h"

class huffman_tree {
public:
    huffman_tree(frequency const &freq);

    unsigned get_count() const;

    ~huffman_tree();

protected:

    std::vector<code_word> symbols;

    struct Node {
        Node *l = nullptr, *r = nullptr;
        unsigned char symbol;
        unsigned long long weight;

        Node() = default;

        Node(Node const &other) = default;

        Node(unsigned long long w, unsigned char c) : weight(w), symbol(c) {}

        Node(unsigned long long w, Node *_l, Node *_r) : weight(w), l(_l), r(_r) {}
    };

    void clear(Node *curr);

    unsigned count;

    void set_symbols(Node *curr, code_word &curr_word);

    Node *root;
};


#endif //HUFFMAN_HUFFMAN_TREE_H
