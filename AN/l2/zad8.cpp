#include <iostream>
#include <cmath>
#include <iomanip>

double f_naiwna(double x) {
    if (x == 0.0) return NAN;
    double licznik = 162.0 * (1.0 - std::cos(5.0 * x));
    double mianownik = x * x;
    return licznik / mianownik;
}

double f_stabilna(double x) {
    double u = 2.5 * x;
    
    if (u == 0.0) {
        return 2025.0;
    }
    
    double sinc = std::sin(u) / u;
    return 2025.0 * (sinc * sinc);
}

int main() {
    std::cout << std::left
              << std::setw(3) << "i"
              << std::setw(12) << "x"
              << std::setw(24) << "Wynik Naiwny"
              << std::setw(24) << "Wynik Stabilny" << std::endl;

    for (int i = 1; i <= 20; ++i) {
        double x_d = std::pow(10.0, -i);

        double result_naiwny = f_naiwna(x_d);
        double result_stabilny = f_stabilna(x_d);

        std::cout << std::scientific << std::setprecision(15);
        std::cout << std::setw(3) << std::right << i << std::left << " "
                  << std::setw(24) << result_naiwny
                  << std::setw(24) << result_stabilny << std::endl;
    }

    return 0;
}
