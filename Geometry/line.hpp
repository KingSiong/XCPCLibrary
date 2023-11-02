#pragma once

#include "./geometry-template.hpp"
#include "./inter.hpp"
#include "./side-of.hpp"

// Mr. Ji
struct Line {
    Point p[2];
    Line(Point _p0 = {0, 0}, Point _p1 = {0, 0}) {
        p[0] = _p0; p[1] = _p1;
    }
    Point &operator [](int id) { return p[id]; }
    bool include(const Point &k) {
        return side_of(p[0], p[1], k) == 1;
    }
    Point dir() { return p[1] - p[0]; }
    friend bool operator<(Line &l1, Line &l2) {
        double a1 = angle(l1.dir());
        double a2 = angle(l2.dir());
        if (!sgn(a1 - a2)) return l2.include(l1[0]);
        return a1 < a2;
    }
};
bool parallel(Line &l1, Line &l2) {
    return !sgn(cross(l1.dir(), l2.dir()));
}
bool same_dir(Line &l1, Line &l2) {
    return parallel(l1, l2) && (sgn(dot(l1.dir(), l2.dir())) == 1);
}
Point line_inter(Line &l1, Line &l2) {
    return line_inter(l1[0], l1[1], l2[0], l2[1]).second;
}
bool check_pos(Line &l1, Line &l2, Line &l) {
    return l.include(line_inter(l1, l2));
}