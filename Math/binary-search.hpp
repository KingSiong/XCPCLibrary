#pragma once

#include "../Template/template.hpp"

// verified by: https://codeforces.com/contest/165/submission/228240241
// f(x) is a non-decresing function
int fun(int x) {
    // return f(x)
}
 
// a[l] <= k < a[r]
// a[l] <= k < mid < a[r]
// a[l] <= mid <= k < a[r]
// answer is r
int upper_bound(int k) {
    int l, r;
    while (r - l > 1) {
        int mid = l + (r - l) / 2;
        if (fun(mid) > k) {
            r = mid;
        } else {
            l = mid;
        }
    }
    return r;
}

// a[l] < k <= a[r]
// a[l] < k <= mid <= a[r]
// a[l] < mid < k <= a[r]
// answer is r
int lower_bound(int k) {
    int l, r;
    while (r - l > 1) {
        int mid = l + (r - l) / 2;
        if (fun(mid) >= k) {
            r = mid;
        } else {
            l = mid;
        }
    }
    return r;
}