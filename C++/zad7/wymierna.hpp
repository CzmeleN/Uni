#pragma once

#include <iostream>
#include <stdexcept>
#include <string>

namespace obliczenia {

class wymierna {
private:
    int nom;
    int den;

public:
    int get_nom() const noexcept;
    int get_den() const noexcept;

    wymierna(int nominator = 0, int denominator = 1);

    friend wymierna operator+(const wymierna& lhs, const wymierna& rhs);
    wymierna& operator+=(const wymierna& rhs);

    friend wymierna operator-(const wymierna& lhs, const wymierna& rhs);
    wymierna& operator-=(const wymierna& rhs);

    friend wymierna operator*(const wymierna& lhs, const wymierna& rhs);
    wymierna& operator*=(const wymierna& rhs);

    friend wymierna operator/(const wymierna& lhs, const wymierna& rhs);
    wymierna& operator/=(const wymierna& rhs);

    wymierna operator-() const;
    wymierna operator!() const;

    operator double() const noexcept;
    explicit operator int() const noexcept;

    friend std::istream& operator>>(std::istream &we, wymierna &w);
    friend std::ostream& operator<<(std::ostream &wy, const wymierna &w);
};

class wyjatek_wymierny : public std::logic_error {
public:
    explicit wyjatek_wymierny(const std::string& msg);
};

class dzielenie_przez_0 : public wyjatek_wymierny {
public:
    dzielenie_przez_0();
};

class przekroczenie_zakresu : public wyjatek_wymierny {
public:
    przekroczenie_zakresu();
};

}
