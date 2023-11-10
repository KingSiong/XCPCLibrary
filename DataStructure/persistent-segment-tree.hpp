#pragma once

#include "../Template/template.hpp"

// verified by: https://judge.yosupo.jp/submission/171016
struct PersistentSegmentTree {
    struct Node {
        Node* l;
        Node* r;
        int x;
        i64 sum = 0;
        Node() : l(nullptr), r(nullptr), x(0), sum(0){};
    };

    std::vector<Node*> node;
    std::vector<int> v;
    int sz = 0;

    PersistentSegmentTree(const std::vector<int>& a) {
        int n = a.size();
        v = a;
        std::sort(begin(v), end(v));
        v.resize(std::unique(begin(v), end(v)) - begin(v));
        sz = v.size();
        node.resize(n + 1);
        node[0] = build(0, sz);
        for (int i = 0; i < n; i++) {
            int p = std::lower_bound(v.begin(), v.end(), a[i]) - v.begin();
            node[i + 1] = add(node[i], 0, sz, p, v[p]);
        }
        return;
    }
    Node* build(int l, int r) {
        auto nt = new Node();
        if (r - l == 1) {
            return nt;
        }

        int m = (l + r) / 2;
        nt->l = build(l, m);
        nt->r = build(m, r);

        return nt;
    }

    Node* add(Node* t, int l, int r, int x, i64 real) {
        Node* nt = new Node();

        if (t) {
            *nt = *t;
        }

        if (r - l == 1) {
            nt->x += 1;
            nt->sum += real;
            return nt;
        }

        int m = (l + r) / 2;

        if (x < m)
            nt->l = add(nt->l, l, m, x, real);
        else
            nt->r = add(nt->r, m, r, x, real);

        nt->x = (nt->l->x) + (nt->r->x);
        nt->sum = (nt->l->sum) + (nt->r->sum);

        return nt;
    }
    std::pair<int, i64> query(Node*& p, Node*& q, int l, int r, int k) {
        if (r - l == 1) {
            int cnt = (q->x) - (p->x);
            i64 sum = (q->sum) - (p->sum);
            if (cnt == 0) return {l, 0};
            return {l, 1LL * sum / cnt * k};
        }
        int cnt = (q->l->x) - (p->l->x);
        int m = (l + r) / 2;

        i64 ret = 0;
        int pos = -1;
        if (k <= cnt) {
            auto [x, y] = query(p->l, q->l, l, m, k);
            pos = x;
            ret += y;
        } else {
            auto [x, y] = query(p->r, q->r, m, r, k - cnt);
            pos = x;
            ret += (q->l->sum) - (p->l->sum) + y;
        }

        return {pos, ret};
    }

    std::pair<int, i64> rangeKth(int l, int r, int k) {
        // [l,r)
        auto [x, sum] = query(node[l], node[r], 0, sz, k);
        return {v[x], sum};
    }
};