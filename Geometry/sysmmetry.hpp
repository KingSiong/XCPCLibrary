#pragma once

#include "./geometry-template.hpp"

// axial symmetry
Point sysmmetry(Point &s, Point &e, Point &r) {
    if (s == e) return s * 2 - r;
    Point p = e - s, q = r - s, num(dot(p, q), cross(p, q));
    return s + Point(dot(num, p), cross(num, p)) / dist2(p);
}
// center symmetry
Point sysmmetry(Point &s, Point &r) {
    return sysmmetry(s, s, r);
}