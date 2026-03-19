#include "shapes.hpp"

#include <cmath>
#include <stdexcept>

constexpr double EPS = 1e-10;

odcinek::odcinek(punkt a, punkt b): a(a), b(b) {
    if (a.x == b.x && a.y == b.y) throw std::invalid_argument ("A i B są takie same");
}

double odcinek::len() {
    return dist(a, b);
}

bool odcinek::is_on(punkt p) {
    return std::abs(dist(a, p) + dist(p, b) - dist(a, b)) < EPS;
}

void odcinek::move(wektor v) {
    a.move(v);
    b.move(v);
}

void odcinek::rotate(punkt o, double deg) {
    a.rotate(o, deg);
    b.rotate(o, deg);
}

void odcinek::mirror(punkt o) {
    a.mirror(o);
    b.mirror(o);
}

void odcinek::mirror(prosta p) {
    a.mirror(p);
    b.mirror(p);
}

bool are_parallel(odcinek a, odcinek b) {
    return std::abs((a.get_b().x - a.get_a().x) * (b.get_b().y - b.get_a().y) -
                    (a.get_b().y - a.get_a().y) * (b.get_b().x - b.get_a().x)) < EPS;
}

bool are_perpendicular(odcinek a, odcinek b) {
    return std::abs((a.get_b().x - a.get_a().x) * (b.get_b().x - b.get_a().x) +
                    (a.get_b().y - a.get_a().y) * (b.get_b().y - b.get_a().y)) < EPS;
}

trojkat::trojkat(punkt a, punkt b, punkt c): a(a), b(b), c(c) {
    if (std::abs(area()) < EPS) throw std::invalid_argument("Punkty trójkąta są współliniowe");
}

double trojkat::perimeter() {
    return dist(a, b) + dist(b, c) + dist(c, a);
}

double trojkat::area() {
    return std::abs((b.x - a.x) * (c.y - a.y) / 2 - (b.y - a.y) * (c.x - a.x) / 2);
}

bool trojkat::is_inside(punkt p) {
    return std::abs(area() - trojkat(p, a, b).area() - trojkat(p, b, c).area() - trojkat(p, c, a).area()) < EPS;
}

void trojkat::move(wektor v) {
    a.move(v);
    b.move(v);
    c.move(v);
}

void trojkat::rotate(punkt o, double deg) {
    a.rotate(o, deg);
    b.rotate(o, deg);
    c.rotate(o, deg);
}

void trojkat::mirror(punkt o) {
    a.mirror(o);
    b.mirror(o);
    c.mirror(o);
}

void trojkat::mirror(prosta p) {
    a.mirror(p);
    b.mirror(p);
    c.mirror(p);
}

bool intersection(punkt a1, punkt b1, punkt a2, punkt b2) {
    enum class Orientation { LINE, CLOCK, COUNTER };
    
    auto get_or = [](punkt p, punkt a, punkt b) {
        const double v = (a.y - p.y) * (b.x - a.x) - (a.x - p.x) * (b.y - a.y);

        if (std::abs(v) < EPS) return Orientation::LINE;

        return (v > 0) ? Orientation::CLOCK : Orientation::COUNTER;
    };

    if (get_or(a1, b1, a2) != get_or(a1, b1, b2) && get_or(a2, b2, a1) != get_or(a2, b2, b1)) return true;

    return false;
}

bool are_disjoint(trojkat a, trojkat b) {
    punkt as[] = {a.get_a(), a.get_b(), a.get_c()};
    punkt bs[] = {b.get_a(), b.get_b(), b.get_c()};
    
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (intersection(as[i], as[(i + 1) % 3], bs[j], bs[(j + 1) % 3])) return false;
        }
    }

    return true;
}

bool is_contained(trojkat a, trojkat b) {
    return a.is_inside(b.get_a()) && a.is_inside(b.get_b()) && a.is_inside(b.get_c());
}
