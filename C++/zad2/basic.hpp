#pragma once

struct wektor {
    double dx, dy;
};

struct prosta {
    double a, b, c;
};

struct punkt {
    double x, y;

    void move(wektor v);
    void rotate(punkt o, double deg);
    void mirror(punkt o);
    void mirror(prosta p);
};

double dist(punkt a, punkt b);
