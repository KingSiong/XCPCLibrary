#pragma once
#include "../Template/template.hpp"

// remind: SA including EMPTY string
// for every len from 1, 2, 4, ...
// c[i]: the rank of s[i...i + len / 2 - 1]
// classes[i]: the rank of s[i...i + len - 1]
// c(len) = classes(len)
// verified by: https://judge.yosupo.jp/problem/suffixarray

// Usage:
//  SuffixArray sa(S);
//  LCPArray lcp(sa);
//  StringSearch search(lcp);
struct SuffixArray {
    int _size;
    vector<int> sa;
    string &s;
    SuffixArray(string &str) : _size(str.size()), s(str) {
        s.push_back(0);
        sa.resize(s.size());
        iota(begin(sa), end(sa), 0);
        sort(begin(sa), end(sa),
             [&](int a, int b) { return s[a] == s[b] ? a > b : s[a] < s[b]; });
        vector<int> classes(s.size()), c(s.begin(), s.end()), cnt(s.size());
        for (int len = 1; len < (int)s.size(); len <<= 1) {
            for (int i = 0; i < (int)s.size(); i++) {
                if (i > 0 && c[sa[i - 1]] == c[sa[i]] &&
                    sa[i - 1] + len < (int)s.size() && // enough condition.
                    c[sa[i - 1] + len / 2] == c[sa[i] + len / 2]) {
                    classes[sa[i]] = classes[sa[i - 1]];
                } else {
                    classes[sa[i]] = i;
                }
            }
            iota(begin(cnt), end(cnt), 0);
            copy(begin(sa), end(sa), begin(c));
            for (int i = 0; i < (int)s.size(); i++) {
                int s1 = c[i] - len;
                if (s1 >= 0) sa[cnt[classes[s1]]++] = s1; // for all s1 belong to [n - len + 1, n], they remain unchanged.
            }
            classes.swap(c);
        }
        s.pop_back();
    }

    void output() {
        cout << "SA\tidx\tstr" << endl;
        for (int i = 0; i < size(); i++) {
            cout << i << ": \t" << sa[i] << " \t";
            if (sa[i] != _size)
                cout << s.substr(sa[i], _size - sa[i]) << endl;
            else
                cout << "$" << endl;
        }
        cout << endl;
    }

    int size() const { return _size + 1; }
    int operator[](int k) const { return sa[k]; }
};

// iterate i from 0, 1, ... n
// lcp(rank[i], rank[i]+1) will decrease at most ONE.
struct LCPArray {
    const SuffixArray &SA;
    vector<int> LCP, rank;
    LCPArray(const SuffixArray &sa) : SA(sa) {
        LCP.resize(SA.size());
        rank.resize(SA.size());
        for (int i = 0; i < SA.size(); i++) {
            rank[SA[i]] = i;
        }
        LCP[0] = 0;

        for (int i = 0, h = 0; i < SA.size() - 1; i++) {
            int j = SA[rank[i] - 1];
            h ? h-- : h;
            while ((i > j ? i : j) + h < SA.size() - 1 &&
                   SA.s[i + h] == SA.s[j + h] && ++h)
                ;
            LCP[rank[i] - 1] = h;
        }
    }

    void output() {
        cout << "SA\tidx\tLCP\tstr" << endl;
        for (int i = 0; i < SA.size(); i++) {
            cout << i << "\t" << SA[i] << " \t" << LCP[i] << "\t";
            if (SA[i] == SA.size() - 1)
                cout << "$";
            else
                cout << SA.s.substr(SA[i], SA.size() - 1 - SA[i]);
            cout << endl;
        }
    }
};