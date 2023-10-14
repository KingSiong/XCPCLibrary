#pragma once

#include "../Template/template.hpp"

// Strongly Connected Components
// Usage: SCC<G> scc(g);
// DAG of SC graph   ... scc.dag (including multiedges)
// new node of k     ... scc[k]
// inv of scc[k] = i ... scc.belong(i)
// verified by: https://judge.yosupo.jp/submission/166266 
template <typename G>
struct SCC {
    const G &g;
    vector<int> dfn, low, stk;
    vector<int> comp;
    vector<vector<int>> blng;
    vector<vector<int>> dag;
    int order, siz;

    SCC(G &_g) : g(_g) { build(); }

    int operator[](int k) { return comp[k]; }

    vector<int> &belong(int i) { return blng[i]; }

    void tarjan(int u) {
        dfn[u] = low[u] = order++;
        stk.push_back(u);
        for (auto v : g[u]) {
            if (dfn[v] == -1) {
                tarjan(v);
                low[u] = min(low[u], low[v]);
            } else {
                low[u] = min(low[u], dfn[v]);
            }
        }
        if (dfn[u] == low[u]) {
            while (true) {
                auto v = stk.back();
                stk.pop_back();
                dfn[v] = g.size();
                comp[v] = siz;
                if (v == u) break;
            }
            ++siz;
        }
    }

    void build() {
        order = siz = 0;
        dfn.resize(g.size(), -1);
        low.resize(g.size(), -1);
        stk.reserve(g.size());
        comp.resize(g.size(), -1);
        for (int i = 0; i < (int)g.size(); i++) {
            if (dfn[i] == -1) {
                tarjan(i);
            }
        }
        dfn.clear();
        dfn.shrink_to_fit();
        low.clear();
        low.shrink_to_fit();
        stk.clear();
        stk.shrink_to_fit();

        dag.resize(siz);
        blng.resize(siz);
        for (int i = 0; i < (int)g.size(); i++) {
            blng[comp[i]].push_back(i);
            for (auto &v : g[i]) {
                int x = comp[i], y = comp[v];
                if (x == y) continue;
                dag[x].push_back(y);
            }
        }
    }
};