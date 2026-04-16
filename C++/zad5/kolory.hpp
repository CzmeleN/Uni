#pragma once

#include <string>
#include <iostream>

class kolor {
private:
    unsigned short r, g, b;

protected:
    void in_bounds(int v) const;

public:
    kolor();
    kolor(int r_v, int g_v, int b_v);

    unsigned short get_r() const;
    unsigned short get_g() const;
    unsigned short get_b() const;

    void set_r(int v);
    void set_g(int v);
    void set_b(int v);

    void brighten(int v = 10);
    void darken(int v = 10);

    static kolor diffuse(const kolor &k1, const kolor &k2);

    friend std::ostream &operator<<(std::ostream &os, const kolor &k);
};

class kolortransparentny : virtual public kolor {
private:
    unsigned short a;

public:
    kolortransparentny();
    kolortransparentny(int r_v, int g_v, int b_v, int a_v);

    unsigned short get_a() const;
    void set_a(int v);
    
    friend std::ostream &operator<<(std::ostream &os, const kolortransparentny &k);
};

class kolornazwany : virtual public kolor {
private:
    std::string name;
    void check_name(const std::string &n) const;

public:
    kolornazwany();
    kolornazwany(int r_v, int g_v, int b_v, const std::string &n);

    std::string get_nazwa() const;
    void set_nazwa(const std::string &n);

    friend std::ostream &operator<<(std::ostream &os, const kolornazwany &k);
};

class kolortn : public kolortransparentny, public kolornazwany {
public:
    kolortn();
    kolortn(int r_v, int g_v, int b_v, int a_v, const std::string &n);

    friend std::ostream &operator<<(std::ostream &os, const kolortn &k);
};

class piksel {
protected:
    int x, y;

public:
    static const int RES_X;
    static const int RES_Y;

    piksel();
    piksel(int x_v, int y_v);

    void set_x(int v);
    void set_y(int v);

    int get_x() const;
    int get_y() const;

    int dist_l() const;
    int dist_r() const;
    int dist_u() const;
    int dist_d() const;

    static double dist(const piksel &p1, const piksel &p2);
    static double dist(const piksel *p1, const piksel *p2);

    friend std::ostream &operator<<(std::ostream &os, const piksel &p);
};

class pikselkolorowy final : public piksel, private kolor {
public:
    pikselkolorowy();
    pikselkolorowy(int x_v, int y_v, int r_v, int g_v, int b_v);

    void move(int dx, int dy);

    using kolor::brighten;

    friend std::ostream &operator<<(std::ostream &os, const pikselkolorowy &p);
};
