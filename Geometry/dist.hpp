#pragma once

#include "./geometry-template.hpp"

// the distance from a point(p) to a line(se)
// be positive when p is on the left side of se, negative instead
double line_dist(Point &s, Point &e, Point &p) {
    return cross(e - s, p - s) / dist(e - s);
}

// the distance from a point(p) to a segment(se)
double seg_dist(Point &s, Point &e, Point &p) {
    if (s == e) return dist(p - s);
    double d = dist2(e - s), t = min(d, max(0.0, dot(p - s, e - s)));
    return dist((p - s) * d - (e - s) * t) / d;
}