#pragma once

#include "../Template/template.hpp"

template <typename T>
struct LinearBasis {
    int n;
    vector<T> basis;

    LinearBasis(int _n = 0) : n(_n) {
        basis.resize(_n);
    }

    T get_max() const {
        T ans = 0;
        for (int i = 0; i < n; i++) {
            ans = max(ans, ans ^ basis[i]);
        }
        return ans;
    }

    void add(T x) {
        for (int i = 0; i < n; i++) {
            x = min(x, x ^ basis[i]);
        }

        if (x != 0) {
            basis.emplace_back(x);
            n = basis.size();
            for (int i = n - 1; i > 0 && basis[i] > basis[i - 1]; i--) {
                swap(basis[i], basis[i - 1]);
            }
        }
    }

    void join(const LinearBasis &B) {
        for (int i = 0; i < B.n; i++) {
            add(B.basis[i]);
        }
    }

    void clear() {
        n = 0;
        basis.clear();
        basis.shrink_to_fit();
    }

    size_t size() const { return n; }

    friend LinearBasis join(const LinearBasis &A, const LinearBasis &B) {
        LinearBasis C = A;
        C.join(B);
        return C;
    }
};