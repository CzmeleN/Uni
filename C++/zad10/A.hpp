#pragma once

#include <iostream>

std::istream& clearline(std::istream& is);

struct ignore_manip {
    int x;
};
ignore_manip ignore(int x);
std::istream& operator>>(std::istream& is, const ignore_manip& m);

std::ostream& comma(std::ostream& os);
std::ostream& colon(std::ostream& os);

struct index_manip {
    int x;
    int w;
};
index_manip index(int x, int w);
std::ostream& operator<<(std::ostream& os, const index_manip& m);
