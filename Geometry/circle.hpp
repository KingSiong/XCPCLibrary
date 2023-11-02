#pragma once

#include "./geometry-template.hpp"

struct Circle {
    Point o; double r;
    Circle(Point _o = {0, 0}, double _r = 0) {
        o = _o, r = _r;
    }
    int position(const Point &p)const {
        return sgn(r - dist(p - o));
    }
};

pair<bool, pair<Point, Point>> circle_inter(Circle &a, Circle &b) {
    if (a.o == b.o) return {false, {Point(0, 0), Point(0, 0)}};
    Point d = b.o - a.o;
    double d2 = dist2(d), sum = a.r + b.r, dif = a.r - b.r, 
           p = (d2 + a.r * a.r - b.r * b.r) / (d2 * 2), h2 = a.r * a.r - p * p * d2;
    if (sum * sum < d2 || dif * dif > d2) return {false, {Point(0, 0), Point(0, 0)}};
    Point mid = a.o + d * p, per = d.perp() * sqrt(max(0.0, h2) / d2);
    return {true, {mid + per, mid - per}};
}

vector<pair<Point, Point>> circle_tan(Circle &a, Circle &b) {
    Point d = b.o - a.o;
    double dr = a.r - b.r, d2 = dist2(d), h2 = d2 - dr * dr;
    if (d2 < EPS || h2 < 0) return {};
    vector<pair<Point, Point>> res;
    for (double sign : {-1, 1}) {
        Point v = (d * dr + d.perp() * sqrt(h2) * sign) / d2;
        res.push_back({a.o + v * a.r, b.o + v * b.r});
    }
    if (h2 < EPS) res.pop_back();
    return res;
}

Circle circumcircle(Point &A, Point &B, Point &C) {
    Point b = C - A, c = B - A;
    Point out = (b * dist2(c) - c * dist2(b)).perp() / cross(b, c) / 2;
    return Circle(A + out, dist(out));
}

// minimum enclosing circle
Circle mec(vector<Point> ps) {
    shuffle(ps.begin(), ps.end(), mt19937(time(0)));
    Circle C(ps[0], 0);
    for (int i = 0; i < ps.size(); ++i) if (C.position(ps[i]) == -1) {
        C = {ps[i], 0};
        for (int j = 0; j < i; ++j) if (C.position(ps[j]) == -1) {
            C = {(ps[i] + ps[j]) / 2, dist(ps[j] - ps[i]) / 2};
            for (int k = 0; k < j; ++k) if (C.position(ps[k]) == -1) {
                C = circumcircle(ps[i], ps[j], ps[k]);
            }
        }
    }
    return C;
}