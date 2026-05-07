#include "wymierna.hpp"
#include <numeric>
#include <cmath>
#include <limits>
#include <unordered_map>

namespace obliczenia {

static void simplify(int& nom, int& den, long long n, long long d) {
    if (d < 0) {
        n = -n;
        d = -d;
    }

    long long g = std::gcd(std::abs(n), d);

    n /= g;
    d /= g;

    if (n < std::numeric_limits<int>::min() || n > std::numeric_limits<int>::max() ||
        d > std::numeric_limits<int>::max())
        throw przekroczenie_zakresu();

    nom = static_cast<int>(n);
    den = static_cast<int>(d);
}

int wymierna::get_nom() const noexcept {
    return nom;
}

int wymierna::get_den() const noexcept {
    return den;
}

wymierna::wymierna(int nominator, int denominator) {
    if (denominator == 0) throw dzielenie_przez_0();

    simplify(nom, den, nominator, denominator);
}

wymierna operator+(const wymierna& lhs, const wymierna& rhs) {
    wymierna res = lhs;

    res += rhs;

    return res;
}

wymierna& wymierna::operator+=(const wymierna& rhs) {
    long long n = static_cast<long long>(nom) * rhs.den +
        static_cast<long long>(rhs.nom) * den;
    long long d = static_cast<long long>(den) * rhs.den;

    simplify(nom, den, n, d);

    return *this;
}

wymierna operator-(const wymierna& lhs, const wymierna& rhs) {
    wymierna res = lhs;

    res -= rhs;

    return res;
}

wymierna& wymierna::operator-=(const wymierna& rhs) {
    long long n = static_cast<long long>(nom) * rhs.den -
        static_cast<long long>(rhs.nom) * den;
    long long d = static_cast<long long>(den) * rhs.den;

    simplify(nom, den, n, d);

    return *this;
}

wymierna operator*(const wymierna& lhs, const wymierna& rhs) {
    wymierna res = lhs;
    res *= rhs;
    return res;
}

wymierna& wymierna::operator*=(const wymierna& rhs) {
    long long n = static_cast<long long>(nom) * rhs.nom;
    long long d = static_cast<long long>(den) * rhs.den;

    simplify(nom, den, n, d);

    return *this;
}


wymierna operator/(const wymierna& lhs, const wymierna& rhs) {
    wymierna res = lhs;

    res /= rhs;

    return res;
}

wymierna& wymierna::operator/=(const wymierna& rhs) {
    if (rhs.nom == 0) throw dzielenie_przez_0();

    long long n = static_cast<long long>(nom) * rhs.den;
    long long d = static_cast<long long>(den) * rhs.nom;

    simplify(nom, den, n, d);

    return *this;
}

wymierna wymierna::operator-() const {
    wymierna res;

    simplify(res.nom, res.den, -static_cast<long long>(nom), den);

    return res;
}

wymierna wymierna::operator!() const {
    if (nom == 0) throw dzielenie_przez_0();

    wymierna res;

    simplify(res.nom, res.den, den, nom);

    return res;
}

wymierna::operator double() const noexcept {
    return static_cast<double>(nom) / den;
}

wymierna::operator int() const noexcept {
    return static_cast<int>(std::round(static_cast<double>(nom) / den));
}

std::istream& operator>>(std::istream &we, wymierna &w) {
    int n, d;
    char c;

    if (we >> n >> c >> d) {
        if (c == '/') w = wymierna(n, d);
        we.setstate(std::ios::failbit);
    }

    return we;
}

std::ostream& operator<<(std::ostream &wy, const wymierna &w) {
    long long n = std::abs(static_cast<long long>(w.nom));
    long long d = w.den;

    if (w.nom < 0) wy << '-';

    wy << (n / d);
    long long rem = n % d;

    if (rem == 0) return wy;

    wy << '.';
    std::string frac = "";
    std::unordered_map<long long, int> seen;
    int pos = 0;

    while (rem != 0 && seen.find(rem) == seen.end()) {
        seen[rem] = pos++;
        rem *= 10;
        frac += std::to_string(rem / d);
        rem %= d;
    }

    if (rem == 0) wy << frac;
    else wy << frac.substr(0, seen[rem]) << '(' << frac.substr(seen[rem]) << ')';

    return wy;
}

wyjatek_wymierny::wyjatek_wymierny(const std::string& msg) : std::logic_error(msg) {}

dzielenie_przez_0::dzielenie_przez_0() : wyjatek_wymierny("dzielenie przez zero") {}

przekroczenie_zakresu::przekroczenie_zakresu() : wyjatek_wymierny("overflow inta") {}

}
