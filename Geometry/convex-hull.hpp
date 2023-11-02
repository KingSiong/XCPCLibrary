#pragma once 

#include "./geometry-template.hpp"

vector<Point> convex_hull(vector<Point> ps) {
    sort(ps.begin(), ps.end());
    vector<Point> h(ps.size() + 1);
    h[0] = ps[0];
    int top = 1;
    for (int i = 1; i < ps.size(); ++i) {
        while (top > 1 && cross(h[top - 1] - h[top - 2], ps[i] - h[top - 1]) <= 0) --top;
        h[top++] = ps[i];
    }
    int down = top;
    for (int i = ps.size() - 2; i; --i) {
        while (top > down && cross(h[top - 1] - h[top - 2], ps[i] - h[top - 1]) <= 0) --top;
        h[top++] = ps[i];
    }
    return {h.begin(), h.begin() + top};
}