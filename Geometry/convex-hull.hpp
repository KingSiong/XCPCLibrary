#pragma once 

#include "./geometry-template.hpp"

vector<Point> convex_hull(vector<Point> p) {
    sort(p.begin(), p.end());
    vector<Point> h(p.size() + 1);
    h[0] = p[0];
    int top = 1;
    for (int i = 1; i < p.size(); ++i) {
        while (top > 1 && cross(h[top - 1] - h[top - 2], p[i] - h[top - 1]) <= 0) --top;
        h[top++] = p[i];
    }
    int down = top;
    for (int i = p.size() - 2; i; --i) {
        while (top > down && cross(h[top - 1] - h[top - 2], p[i] - h[top - 1]) <= 0) --top;
        h[top++] = p[i];
    }
    return {h.begin(), h.begin() + top};
}