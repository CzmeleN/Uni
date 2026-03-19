#include "basic.hpp"

#include <cmath>
#include <stdexcept>

void punkt::move(wektor v) {
    x += v.dx;
    y += v.dy;
}

void punkt::rotate(punkt o, double deg) {
    const double rad = deg * M_PI / 180.0;
    const double s = sin(rad);
    const double c = cos(rad);

    const double mx = x - o.x;
    const double my = y - o.y;

    x = mx * c - my * s + o.x;
    y = mx * s + my * c + o.y;
}

void punkt::mirror(punkt o) {
    x = o.x + o.x - x;
    y = o.y + o.y - y;
}

void punkt::mirror(prosta p) {
    if (p.a == 0 && p.b == 0) throw std::invalid_argument("A i B prostej == 0");

    x = x - 2 * p.a * (p.a * x + p.b * y + p.c) / (p.a * p.a + p.b * p.b);
    y = y - 2 * p.b * (p.a * x + p.b * y + p.c) / (p.a * p.a + p.b * p.b);
}

double dist(punkt a, punkt b) {
    return std::sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}
