#include <iostream>
#include <cmath>
#include <iomanip>

double f_naiwna(double x) {
    double x15 = std::pow(x, 15);
    if (x15 == 0) {
        return NAN;
    }
    double licznik_wewnatrz_pierwiastka = 12150.0 * x15 + 9.0;
    double licznik = std::sqrt(licznik_wewnatrz_pierwiastka) - 3.0;
    return licznik / x15;
}

double f_stabilna(double x) {
    double x15 = std::pow(x, 15);
    double mianownik_wewnatrz_pierwiastka = 12150.0 * x15 + 9.0;
    double mianownik = std::sqrt(mianownik_wewnatrz_pierwiastka) + 3.0;
    
    if (mianownik == 0) {
        return NAN;
    }
    return 12150.0 / mianownik;
}

int main() {
    double x = 0.01;

    std::cout << std::fixed << std::setprecision(20);

    std::cout << "--- Eksperyment Numeryczny dla f(x) ---" << std::endl;
    std::cout << "x = " << x << std::endl;

    double x15 = std::pow(x, 15);
    double w1 = 12150.0 * x15;
    double w2 = w1 + 9.0;
    double w3 = std::sqrt(w2);
    
    std::cout << "Analiza metody naiwnej:" << std::endl;
    std::cout << "x^15                 = " << x15 << std::endl;
    std::cout << "12150 * x^15         = " << w1 << std::endl;
    std::cout << "12150 * x^15 + 9     = " << w2 << " (!!!)\n";
    std::cout << "sqrt(...)            = " << w3 << std::endl;
    std::cout << "sqrt(...) - 3        = " << (w3 - 3.0) << std::endl;
    std::cout << std::endl;

    double wynik_naiwny = f_naiwna(x);
    double wynik_stabilny = f_stabilna(x);

    std::cout << "--- Wyniki Końcowe ---" << std::endl;
    std::cout << "Wynik algorytmu naiwnego:   " << wynik_naiwny << std::endl;
    std::cout << "Wynik algorytmu stabilnego: " << wynik_stabilny << std::endl;
    
    return 0;
}
