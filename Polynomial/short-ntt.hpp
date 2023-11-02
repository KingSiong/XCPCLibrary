#pragma once 

#include "../Template/template.hpp"

// verified by: https://contest.ucup.ac/submission/235652
int f_pow(int base, int b, int mod) {
    int res = 1;
    while (b) {
        if (b & 1) res = 1ll * res * base % mod;
        base = 1ll * base * base % mod;
        b >>= 1;
    }
    return res;
}

// mod 998244353
struct NTT {
    vector<int> rev;
    vector<int> roots{0, 1};
    static constexpr int MOD = 998244353;
    static constexpr int rt = 3;

    void dft(vector<int> &a) {
        int n = a.size();

        if ((int)(rev.size()) != n) {
            int k = __builtin_ctz(n) - 1;
            rev.resize(n);
            for (int i = 0; i < n; i++) {
                rev[i] = rev[i >> 1] >> 1 | (i & 1) << k;
            }
        }

        for (int i = 0; i < n; i++) {
            if (rev[i] < i) {
                swap(a[i], a[rev[i]]);
            }
        }
        if ((int)(roots.size()) < n) {
            int k = __builtin_ctz(roots.size());
            roots.resize(n);
            while ((1 << k) < n) {
                int e = f_pow(rt, (MOD - 1) >> (k + 1), MOD);
                for (int i = 1 << (k - 1); i < (1 << k); i++) {
                    roots[2 * i] = roots[i];
                    roots[2 * i + 1] = 1ll * roots[i] * e % MOD;
                }
                k++;
            }
        }
        for (int k = 1; k < n; k *= 2) {
            for (int i = 0; i < n; i += 2 * k) {
                for (int j = 0; j < k; j++) {
                    int u = a[i + j];
                    int v = 1ll * a[i + j + k] * roots[k + j] % MOD;
                    a[i + j] = (1ll * u + v) % MOD;
                    a[i + j + k] = (1ll * u - v + MOD) % MOD;
                }
            }
        }
    }
    void idft(vector<int> &a) {
        int n = a.size();
        reverse(a.begin() + 1, a.end());
        dft(a);
        int inv = f_pow(n, MOD - 2, MOD);
        for (int i = 0; i < n; i++) {
            a[i] = 1ll * a[i] * inv % MOD;
        }
    }
    vector<int> multiply(vector<int> a, vector<int> b) {
        int sz = 1, tot = (int)a.size() + (int)b.size() - 1;

        while (sz < tot) {
            sz *= 2;
        }

        a.resize(sz), b.resize(sz);
        dft(a), dft(b);

        for (int i = 0; i < sz; i++) {
            a[i] = 1ll * a[i] * b[i] % MOD;
        }

        idft(a);
        a.resize(tot);
        return a;
    }
};