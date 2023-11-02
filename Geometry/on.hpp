#pragma once

#include "./geometry-template.hpp"
#include "./dist.hpp"

bool on_seg(Point &s, Point &e, Point &p) {
    return seg_dist(s, e, p) < EPS;
}

bool on_line(Point &s, Point &e, Point &p) {
    return line_dist(s, e, p) < EPS;
}