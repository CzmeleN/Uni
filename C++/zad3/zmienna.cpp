#include "zmienna.hpp"

#include <stdexcept>

void zmienna::init_hist() {
    hist = new double[size];
    hist[0] = val;
}

zmienna::zmienna(std::string n, double v) : name(std::move(n)), val(v) {
    init_hist();
}

zmienna::zmienna() : zmienna("x", 0.0) {}

zmienna::zmienna(const zmienna &x) : name(x.name), val(x.val) {
    init_hist();
}

zmienna::zmienna(zmienna &&x) noexcept : name(x.name), val(x.val), start(x.start), curr(x.curr), hist(x.hist) {
    x.hist = nullptr;
}

zmienna& zmienna::operator= (const zmienna& x) {
    if (this == &x) return *this;
    set(x.val);
    return *this;
}

zmienna& zmienna::operator= (zmienna&& x) noexcept {
    if (this == &x) return *this;
    set(x.val);
    return *this;
}

zmienna::~zmienna() {
    delete[] hist;
}

double zmienna::get() const {
    return val;
}

void zmienna::set(double x) {
    if (++curr == size) curr = 0;

    if (curr == start) ++start;
    if (start == size) start = 0;

    hist[curr] = x;
    val = x;
}

void zmienna::restore() {
    if (curr == start) return;

    if (curr == 0) curr = size;
    val = hist[--curr];
}

void zmienna::neg() {
    set(-val);
}

void zmienna::inv() {
    if (val == 0.0) throw std::domain_error("próba dzielenia przez 0");
    set(1 / val);
}
