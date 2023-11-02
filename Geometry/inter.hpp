#pragma once

#include "./geometry-template.hpp"
#include "./on.hpp"
#include "./line.hpp"

vector<Point> seg_inter(Point &s1, Point &e1, Point &s2, Point &e2) {
    double oa = cross(e2 - s2, s1 - s2), ob = cross(e2 - s2, e1 - s2);
    double oc = cross(e1 - s1, s2 - s1), od = cross(e1 - s1, e2 - s1);
    if (sgn(oa) * sgn(ob) < 0 && sgn(oc) * sgn(od) < 0) {
        return {(s1 * ob - e1 * oa) / (ob - oa)};
    }
    set<Point> s;
    if (on_seg(s2, e2, s1)) s.insert(s1);
    if (on_seg(s2, e2, e1)) s.insert(e1);
    if (on_seg(s1, e1, s2)) s.insert(s2);
    if (on_seg(s1, e1, e2)) s.insert(e2);
    return {s.begin(), s.end()};
}

//1: one intersection; -1: infinite many; 0: null
pair<int, Point> line_inter(Point &s1, Point &e1, Point &s2, Point &e2) {
    double d = cross(e1 - s1, e2 - s2);
    if (!sgn(d)) return {-(sgn(cross(e1 - s1, e2 - s1)) == 0), Point(0, 0)};
    double p = cross(e1 - s2, e2 - s2), q = cross(e2 - s2, s1 - s2);
    return {1, (s1 * p + e1 * q) / d};
}

Point line_inter(Line &l1, Line &l2) {
    return line_inter(l1[0], l1[1], l2[0], l2[1]).second;
}