#pragma once
#include "../Template/template.hpp"

/*
verified by: https://codeforces.com/problemset/problem/126/B
z[0] = 0
*/

vector<int> z_fun(const string &s) {
    int n = s.size();
    vector<int> z(n);
    for (int i = 1, l = 0, r = 0; i < n; ++i) {
        int k = (i <= r && z[i - l] < (r - i + 1)) ? z[i - l] : max(0, r - i + 1);
        while (i + k < n && s[k] == s[i + k]) ++k;
        z[i] = k--;
        if (i + k > r) l = i, r = i + k;
    }
    return z;
}