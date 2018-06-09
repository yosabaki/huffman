//
// Created by Artem Ustinov on 6/1/2018.
//

#include <cstdint>
#include <algorithm>

#include "huffman_tree.h"

huffman_tree::huffman_tree(frequency const &freq) {
    count = 0;
    int n = freq.size();
    symbols.resize(256);
    tree.resize(2 * n);
    std::vector<std::pair<unsigned long long, unsigned char>> tmp_freq;
    for (int i = 0; i < 256; i++) {
        if (freq[i] != 0) {
            tmp_freq.push_back({freq[i], i});
        }
    }
    std::sort(tmp_freq.begin(), tmp_freq.end());
    for (size_t i = 0; i < n; i++) {
        tree[i + 1] = Node(tmp_freq[i].first, tmp_freq[i].second, i + 1);
    }
    size_t l = 1, r = n + 1;
    for (int i = 0; i < n - 1; i++) {
        Node t1, t2;
        if (l <= n && tree[l].weight <= tree[r].weight) {
            t1 = tree[l];
            l++;
        } else {
            t1 = tree[r];
            r++;
        }
        if (l <= n && tree[l].weight <= tree[r].weight) {
            t2 = tree[l];
            l++;
        } else {
            t2 = tree[r];
            r++;
        }
        tree[i + n + 1] = Node(t1.weight + t2.weight, t1.ind, t2.ind, i + n + 1);
    }
    if (n == 0) {
        root = 0;
    } else if (n == 1) {
        tree.push_back(Node(tree[0].weight, 1, 0, 2));
        root = 2;
    } else {
        root = 2 * n - 1;
    }
    code_word ctmp = code_word();
    set_symbols(root, ctmp);
}


unsigned huffman_tree::get_count() const {
    return count;
}

void huffman_tree::set_symbols(size_t curr, code_word &curr_word) {
    if (curr == 0) return;
    if (tree[curr].l != 0) {
        curr_word.push_bit(true);
        set_symbols(tree[curr].l, curr_word);
        curr_word.pop_bit();
        if (tree[curr].r != 0) {
            curr_word.push_bit(false);
            set_symbols(tree[curr].r, curr_word);
            curr_word.pop_bit();
        }
    } else {
        count += curr_word.length * tree[curr].weight;
        symbols[tree[curr].symbol] = curr_word;
    }
}
