#pragma once
#include "trie.hpp"

/*
next(i, X) <=> suffix-link(i) <=> fail-link(i)
verified by: https://www.luogu.com.cn/problem/P5357
*/

template <size_t X = 26, char margin = 'a'>
struct AhoCorasick : Trie<X + 1, margin> {
    using TRIE = Trie<X + 1, margin>;
    using TRIE::next;
    using TRIE::st;
    using TRIE::TRIE; // i copied this from japanese, which can be deleted, i guess.
    vector<int> cnt; // count all matched patterns when passing by i chars.

    void build() {
        int n = st.size();
        cnt.resize(n);
        for (int i = 0; i < n; i++) {
            cnt[i] = st[i].idxs.size();
        }

        queue<int> que;
        for (int i = 0; i < (int)X; i++) {
            if (~next(0, i)) {
                next(next(0, i), X) = 0;
                que.emplace(next(0, i));
            } else {
                next(0, i) = 0;
            }
        }

        while (!que.empty()) {
            auto &x = st[que.front()];
            int fail = x.nxt[X];

            cnt[que.front()] += cnt[fail];
            que.pop();

            for (int i = 0; i < (int)X; i++) {
                int &nx = x.nxt[i];
                if (nx < 0) {
                    nx = next(fail, i);
                    continue;
                }
                que.emplace(nx);
                next(nx, X) = next(fail, i);
            }
        }
    }

    int count(int pos) { return cnt[pos]; }
};