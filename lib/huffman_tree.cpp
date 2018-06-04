//
// Created by Artem Ustinov on 6/1/2018.
//

#include <cstdint>
#include "huffman_tree.h"
#include <algorithm>

huffman_tree::huffman_tree(frequency const &freq) {
    count = 0;
    int n = freq.size();
    symbols.resize(256);
    std::vector<Node> tmp_symb(n, Node(0, 0));
    std::vector<std::pair<unsigned long long, unsigned char>> tmp_freq;
    for (int i = 0; i < 256; i++) {
        if (freq[i] != 0) {
            tmp_freq.push_back({freq[i], i});
        }
    }
    std::sort(tmp_freq.begin(), tmp_freq.end());
    for (int i = 0; i < n; i++) {
        tmp_symb[i] = Node(tmp_freq[i].first, tmp_freq[i].second);
    }

    std::vector<Node> tmp(n, Node(UINT32_MAX, 0));
    size_t l = 0, r = 0;
    for (int i = 0; i < n - 1; i++) {
        Node *t1, *t2;
        if (l < n && tmp_freq[l].first <= tmp[r].weight) {
            t1 = new Node(tmp_symb[l]);
            l++;
        } else {
            t1 = new Node(tmp[r]);
            r++;
        }
        if (l < n && tmp_freq[l].first <= tmp[r].weight) {
            t2 = new Node(tmp_symb[l]);
            l++;
        } else {
            t2 = new Node(tmp[r]);
            r++;
        }
        tmp[i] = Node(t1->weight + t2->weight, t1, t2);
    }
    if (n == 0) {
        root = nullptr;
        return;
    }
    if (n == 1) {
        root = new Node(tmp_freq[0].first, new Node(tmp_symb[0]), nullptr);
    } else {
        root = new Node(tmp[tmp.size() - 2]);
    }
    code_word ctmp = code_word();
    set_symbols(root, ctmp);
}

huffman_tree::~huffman_tree() {
    if (root != nullptr)
        clear(root);
    delete (root);
}

void huffman_tree::clear(Node *curr) {
    if (curr->l != nullptr) {
        clear(curr->l);
        delete (curr->l);
        if (curr->r != nullptr) {
            clear(curr->r);
            delete (curr->r);
        }
    } else return;
}

unsigned huffman_tree::get_count() const {
    return count;
}

void huffman_tree::set_symbols(Node *curr, code_word &curr_word) {
    if (curr->l != nullptr) {
        curr_word.push_bit(true);
        set_symbols(curr->l, curr_word);
        curr_word.pop_bit();
        if (curr->r != nullptr) {
            curr_word.push_bit(false);
            set_symbols(curr->r, curr_word);
            curr_word.pop_bit();
        }
    } else {
        count += curr_word.length * curr->weight;
        symbols[curr->symbol] = curr_word;
    }
}
