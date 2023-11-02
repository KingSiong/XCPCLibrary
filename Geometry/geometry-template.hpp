#pragma once

#include "../Template/template.hpp"

const double EPS = 1e-6;

template<class T> int sgn(T x) { return (x > 0) - (x < 0); }
struct Point {
    double x, y;
    Point(double _x = 0, double _y = 0) : x(_x), y(_y) {}
    Point operator+(const Point &p) const {
        return Point(x + p.x, y + p.y);
    }
    Point operator-(const Point &p) const {
        return Point(x - p.x, y - p.y);
    }
    Point operator*(double w) const {
        return Point(x * w, y * w);
    }
    Point operator/(double w) const {
        return Point(x / w, y / w);
    }
    bool operator==(const Point &p) const {
        return tie(x, y) == tie(p.x, p.y);
    }
    bool operator<(const Point &p) const {
        return tie(x, y) < tie(p.x, p.y);
    }
    Point unit() const { return *this / sqrt(x * x + y * y); }
    Point perp() const { return Point(-y, x); }
    Point normal() const { return perp().unit(); }
    void print() {
        printf("(%lf %lf)\n", x, y);
    }
};
double dist2(const Point &p) {
    return p.x * p.x + p.y * p.y;
}
double dist(const Point &p) {
    return sqrt(p.x * p.x + p.y * p.y);
}
double dot(const Point &a, const Point &b) {
    return a.x * b.x + a.y * b.y;
}
double cross(const Point &a, const Point &b) {
    return a.x * b.y - b.x * a.y;
}
Point rotate(const Point &a, double theta) {
    return Point(a.x * cos(theta) - a.y * sin(theta), a.y * cos(theta) + a.x * sin(theta));
}
double angle(const Point &p) {
    return atan2(p.y, p.x);
}