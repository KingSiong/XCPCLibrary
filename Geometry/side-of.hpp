#pragma once

#include "./geometry-template.hpp"

int side_of(const Point &s, const Point &e, const Point &p) {
    double a = cross(e - s, p - s), l = dist(e - s) * EPS;
    return (a > l) - (a < -l);
}