#pragma once

#include "./geometry-template.hpp"

pair<Point, Point> hull_diameter(vector<Point> h) {
    int n = h.size(), j = n < 2 ? 0 : 1;
    pair<double, pair<Point, Point>> res({0, {h[0], h[0]}});
    for (int i = 0; i < j; ++i) {
        for (;; j = (j + 1) % n) {
            res = max(res, {dist2(h[i] - h[j]), {h[i], h[j]}});
            if (cross(h[(j + 1) % n] - h[j], h[i + 1] - h[i]) >= 0) break;
        }
    }
    return res.second;
}