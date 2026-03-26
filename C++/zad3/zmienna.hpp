#pragma once

#include <string>

class zmienna {
private:
    static constexpr size_t size = 3;
    const std::string name;
    double val;
    size_t start = 0, curr = 0;
    double *hist = nullptr;

    void init_hist();

public:
    zmienna();
    zmienna(std::string n, double v);
    zmienna(const zmienna &x);
    zmienna(zmienna &&x) noexcept;

    zmienna& operator= (const zmienna& x);
    zmienna& operator= (zmienna&& x) noexcept;

    ~zmienna();

    double get() const;
    void set(double x);
    void restore();

    void neg();
    void inv();
};

