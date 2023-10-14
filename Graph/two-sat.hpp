#pragma once

#include "../Template/template.hpp"
#include "./tarjan-scc.hpp"

// verified by: https://judge.yosupo.jp/submission/166271
// at_most_one() was verified by: https://www.luogu.com.cn/record/129427111 
// and https://pintia.cn/problem-sets/1705510247604809728/exam/problems/1705514248467492866?type=7&page=0
struct TwoSat {
    using Edges = vector<int>;
    using G = vector<Edges>;
    G g;
    int _n;
    bool built;
    vector<int> _ans;

    TwoSat(int n = 0) : _n(n), built(false) {
        if (n > 0) {
            g.resize(n * 2);
        }
    }

    int add_var() {
        g.emplace_back(Edges());
        g.emplace_back(Edges());
        return _n++;
    }

    void add_edge(int u, int v) { g[u].emplace_back(v); }

    void add_clause(int i, int j) {
        i = max(i * 2, -1 - i * 2);
        j = max(j * 2, -1 - j * 2);
        assert(0 <= i && i < _n * 2);
        assert(0 <= j && j < _n * 2);
        add_edge(i ^ 1, j);
        add_edge(j ^ 1, i);
    }
    void if_then(int i, int j) { add_clause(~i, j); }
    void set_val(int i) { add_clause(i, i); }
    void at_most_one(const vector<int> &nodes, bool one_flag = false) {
        if ((int)nodes.size() <= 1) return;
        int cur = nodes[0];
        for (int i = 1; i < (int)nodes.size(); i++) {
            auto nxt = add_var(), node = nodes[i];
            add_clause(~cur, ~node);
            add_clause(~cur, nxt);
            add_clause(~node, nxt);
            cur = nxt;
        }
        if (one_flag) set_val(cur);
    }
    void exactly_one(const vector<int> &nodes) { at_most_one(nodes, true); }

    bool satisfiable() {
        _ans.resize(_n);
        built = true;
        SCC<G> scc(g);
        for (int i = 0; i < _n; i++) {
            if (scc[i * 2] == scc[i * 2 + 1]) {
                _ans.clear();
                _ans.shrink_to_fit();
                return false;
            }
            _ans[i] = scc[i * 2] < scc[i * 2 + 1];
        }
        return true;
    }
    vector<int> answer() {
        if (!built) satisfiable();
        return _ans;
    }
};