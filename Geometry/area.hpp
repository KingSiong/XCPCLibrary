#pragma once 

#include "./geometry-template.hpp"
#include "./Line.hpp"

double get_area(vector<Point> &p) {
    double res = 0;
    int n = p.size();
    if (n < 3) return res;
    for (int i = 1; i < n - 1; ++i) {
        res += cross(p[i] - p[0], p[i + 1] - p[0]);
    }
    return res / 2;
}

double get_area(vector<Line> &L) {
    vector<Point> p;
    for (int i = 0; i < L.size(); ++i) {
        p.push_back(line_inter(L[i], L[(i + 1) % L.size()]));
    }
    return get_area(p);
}