#include "A.hpp"

#include <iomanip>

std::istream& clearline(std::istream& is) {
    int c;

    while ((c = is.get())) {
        if (c == '\n') break;
    }

    return is;
}

ignore_manip ignore(int x) {
    return {x};
}

std::istream& operator>>(std::istream& is, const ignore_manip& m) {
    for (int i = 0; i < m.x; ++i) {
        int c = is.get();

        if (!c || c == '\n') break;
    }

    return is;
}

std::ostream& comma(std::ostream& os) {
    return os << ", ";
}

std::ostream& colon(std::ostream& os) {
    return os << ": ";
}

index_manip index(int x, int w) {
    return {x, w};
}

std::ostream& operator<<(std::ostream& os, const index_manip& m) {
    return os << "[" << std::setw(m.w) << std::right << m.x << "]";
}
