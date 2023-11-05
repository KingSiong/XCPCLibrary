#pragma once 

#include "../Template/template.hpp"

// verified by: https://www.luogu.com.cn/record/133457030
struct Query {
    int l, r, idx;
    Query(int _l = 0, int _r = 0, int _idx = 0) : l(_l), r(_r), idx(_idx) {}
};

vector<int> cnt, col;

// n is the range, and m is the number of queries
int n, m;
int tot = 0;

// TODO: add an end to the state
// C(x, 2) - C(x - 1, 2) = C(x - 1, 1)
void add(int i) {
    tot += cnt[col[i]];
    cnt[col[i]]++;
}

// TODO: del an end to the state
// C(x - 1, 2) - C(x, 2) = -C(x - 1, 1)
void del(int i) {
    cnt[col[i]]--;
    tot -= cnt[col[i]];
}

int gcd(int a, int b) { return b ? gcd(b, a % b) : a; }

void solve() {
    int block = (int)(1.0 * n / sqrt(m + 0.5));
    vector<Query> q(m);
    for (int i = 0; i < m; i++) {
        int l, r; cin >> l >> r; --l; --r;
        q[i] = Query(l, r, i);
    }
    sort(begin(q), end(q), [&](const auto &A, const auto &B) -> bool {
        if (A.l / block != B.l / block) return A.l < B.l;
        if (A.l / block & 1) {
            return A.r < B.r;
        } else {
            return A.r > B.r;
        }
    });
    vector<int> up(m, 0), len(m, 0);
    for (int i = 0, l = 1, r = 0; i < m; i++) {
        const auto [_l, _r, idx] = q[i];
        while (l > _l) add(--l);
        while (r < _r) add(++r);
        while (l < _l) del(l++);
        while (r > _r) del(r--);
        // TODO: update the ans of query #idx
        up[idx] = tot;
        len[idx] = _r - _l + 1;
    }
    for (int i = 0; i < m; i++) {
        if (len[i] <= 1) {
            cout << "0/1\n";
        } else {
            int down = len[i] * (len[i] - 1) / 2;
            int d = gcd(up[i], down);
            cout << up[i] / d << "/" << down / d << "\n";
        }
    }
} 