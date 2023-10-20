#pragma once 

#include "../Template/template.hpp"

// sweep line algorithm
// [1, n] has no intervals initial
// seg[1] returns the length of union of intervals
// we can add a [l, r] into the segment tree
// but only can delete a [l, r] while it has been added and not been deleted yet (still in segment tree)
// verified by: https://contest.ucup.ac/submission/220322
// int tag[MAX_N << 2], seg[MAX_N << 2];
vector<int> tag, seg;

void pushup(int u, int l, int r) {
    if (tag[u] > 0) {
        seg[u] = r - l + 1;
    } else if (l < r) {
        seg[u] = seg[u << 1] + seg[u << 1 | 1]; 
    } else {
        seg[u] = 0;
    }
}

void modify(int u, int l, int r, int x, int y, int d) {
    if (x <= l && r <= y) {
        tag[u] += d;
    } else {
        int mid = (l + r) / 2;
        if (x <= mid && y >= l) modify(u << 1, l, mid, x, y, d);
        if (y > mid && x <= r) modify(u << 1 | 1, mid + 1, r, x, y, d);
    }
    pushup(u, l, r);
}