#include "kolory.hpp"
#include <stdexcept>
#include <cmath>

void kolor::in_bounds(int v) const {
    if (v < 0 || v > 255) throw std::out_of_range("wartość koloru musi być w zakresie 0-255");
}

kolor::kolor() : r(0), g(0), b(0) {}

kolor::kolor(int r_v, int g_v, int b_v) {
    in_bounds(r_v); 
    in_bounds(g_v); 
    in_bounds(b_v);
    r = r_v; 
    g = g_v; 
    b = b_v;
}

unsigned short kolor::get_r() const {
    return r;
}

unsigned short kolor::get_g() const {
    return g;
}

unsigned short kolor::get_b() const { 
    return b;
}

void kolor::set_r(int v) {
    in_bounds(v);
    r = v;
}

void kolor::set_g(int v) {
    in_bounds(v);
    g = v;
}

void kolor::set_b(int v) {
    in_bounds(v);
    b = v;
}

void kolor::brighten(int v) {
    r = std::min(255, r + v);
    g = std::min(255, g + v);
    b = std::min(255, b + v);
}

void kolor::darken(int v) {
    r = std::max(0, r - v);
    g = std::max(0, g - v);
    b = std::max(0, b - v);
}

kolor kolor::diffuse(const kolor& k1, const kolor& k2) {
    return kolor((k1.r + k2.r) / 2, (k1.g + k2.g) / 2, (k1.b + k2.b) / 2);
}

std::ostream& operator<<(std::ostream& os, const kolor& k) {
    os << "RGB(" << k.r << ',' << k.g << ',' << k.b << ')';

    return os;
}

kolortransparentny::kolortransparentny() : kolor(), a(255) {}

kolortransparentny::kolortransparentny(int r_v, int g_v, int b_v, int a_v)
    : kolor(r_v, g_v, b_v) {
    set_a(a_v);
}

unsigned short kolortransparentny::get_a() const {
    return a;
}

void kolortransparentny::set_a(int v) {
    in_bounds(v);
    a = v;
}

std::ostream& operator<<(std::ostream& os, const kolortransparentny& k) {
    os << "RGBA(" << k.get_r() << ',' << k.get_g() << ',' << k.get_b() << ", a:" << k.a << ')';

    return os;
}

void kolornazwany::check_name(const std::string& n) const {
    for (char c : n) {
        if (!std::islower(c)) {
            throw std::invalid_argument("nazwa koloru musi składać się tylko z małych liter");
        }
    }
}

kolornazwany::kolornazwany() : kolor(), name("") {}

kolornazwany::kolornazwany(int r_v, int g_v, int b_v, const std::string& n)
    : kolor(r_v, g_v, b_v) {
    set_nazwa(n);
}

std::string kolornazwany::get_nazwa() const { return name; }

void kolornazwany::set_nazwa(const std::string& n) {
    if (!n.empty()) check_name(n);
    name = n;
}

std::ostream& operator<<(std::ostream& os, const kolornazwany& k) {
    os << "kolor(" << k.name << ") - RGB(" << k.get_r() << ',' << k.get_g() << ',' << k.get_b() << ')';
    return os;
}

kolortn::kolortn() : kolor(), kolortransparentny(), kolornazwany() {}

kolortn::kolortn(int r_v, int g_v, int b_v, int a_v, const std::string& n) : kolor(r_v, g_v, b_v), 
      kolortransparentny(r_v, g_v, b_v, a_v), 
      kolornazwany(r_v, g_v, b_v, n) {}

std::ostream& operator<<(std::ostream& os, const kolortn& k) {
    os << "kolorTN(" << k.get_nazwa() << ") - RGBA(" 
       << k.get_r() << ',' << k.get_g() << ',' << k.get_b() << ',' << k.get_a() << ')';
    return os;
}

const int piksel::RES_X = 1920;
const int piksel::RES_Y = 1080;

piksel::piksel() : x(0), y(0) {}

piksel::piksel(int x_v, int y_v) {
    set_x(x_v);
    set_y(y_v);
}

void piksel::set_x(int v) {
    if (v < 0 || v >= RES_X) throw std::out_of_range("x poza ekranem");
    x = v;
}

void piksel::set_y(int v) {
    if (v < 0 || v >= RES_Y) throw std::out_of_range("y poza ekranem");
    y = v;
}

int piksel::get_x() const {
    return x;
}

int piksel::get_y() const {
    return y;
}

int piksel::dist_l() const {
    return x;
}

int piksel::dist_r() const {
    return RES_X - 1 - x;
}

int piksel::dist_u() const {
    return y;
}

int piksel::dist_d() const {
    return RES_Y - 1 - y;
}

double piksel::dist(const piksel& p1, const piksel& p2) {
    return std::sqrt(std::pow(p1.x - p2.x, 2) + std::pow(p1.y - p2.y, 2));
}

double piksel::dist(const piksel* p1, const piksel* p2) {
    if (!p1 || !p2) throw std::invalid_argument("przekazano wskaźnik/-i null");

    return std::sqrt(std::pow(p1->x - p2->x, 2) + std::pow(p1->y - p2->y, 2));
}

std::ostream& operator<<(std::ostream& os, const piksel& p) {
    os << "piksel(" << p.x << ", " << p.y << ')';

    return os;
}

pikselkolorowy::pikselkolorowy() : piksel(), kolor() {}

pikselkolorowy::pikselkolorowy(int x_v, int y_v, int r_v, int g_v, int b_v) :
    piksel(x_v, y_v), kolor(r_v, g_v, b_v) {}

void pikselkolorowy::move(int dx, int dy) {
    set_x(x + dx); 
    set_y(y + dy);
}

std::ostream& operator<<(std::ostream& os, const pikselkolorowy& p) {
    os << static_cast<const piksel&>(p) << " - " << static_cast<const kolor&>(p);

    return os;
}
