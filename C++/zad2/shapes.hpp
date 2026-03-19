#pragma once

#include "basic.hpp"

class odcinek {
private:
    punkt a, b;

public:
    odcinek(punkt a, punkt b);

    punkt get_a() { return a; };
    punkt get_b() { return b; };

    double len();
    bool is_on(punkt a);
    void move(wektor v);
    void rotate(punkt o, double deg);
    void mirror(punkt o);
    void mirror(prosta p);
};

bool are_parallel(odcinek a, odcinek b);
bool are_perpendicular(odcinek a, odcinek b);

class trojkat {
private:
    punkt a, b, c;

public:
    trojkat(punkt a, punkt b, punkt c);

    punkt get_a() { return a; };
    punkt get_b() { return b; };
    punkt get_c() { return c; };

    double perimeter();
    double area();
    bool is_inside(punkt a);
    void move(wektor v);
    void rotate(punkt o, double deg);
    void mirror(punkt o);
    void mirror(prosta p);
};

bool are_disjoint(trojkat a, trojkat b);
bool is_contained(trojkat a, trojkat b);
