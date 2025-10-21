#include <iostream>
#include <cmath>
#include <iomanip>

const double PI_REF = 3.14159265358979323846;

double ciag_naiwny(double x_k, int k) {
    double pow_2k = std::pow(2.0, k);
    double y_k_sq = std::pow(x_k / pow_2k, 2.0);
    double inner_sqrt = std::sqrt(1.0 - y_k_sq);
    double inner_expr = 2.0 * (1.0 - inner_sqrt);
    
    return pow_2k * std::sqrt(inner_expr);
}

double ciag_stabilny(double x_k, int k) {
    double y_k_sq = std::pow(x_k / std::pow(2.0, k), 2.0);
    double inner_sqrt = std::sqrt(1.0 - y_k_sq);
    double denominator = std::sqrt(1.0 + inner_sqrt);
    
    return std::sqrt(2.0) * x_k / denominator;
}

int main() {
    std::cout << std::fixed << std::setprecision(18);
    std::cout << "Prawdziwa wartosc Pi: " << PI_REF << std::endl;
    std::cout << std::left << std::setw(3) << "k"
              << std::setw(25) << "x_k (Naiwny)"
              << std::setw(25) << "x_k (Stabilny)"
              << "Blad (Naiwny)" << std::endl;

    double x_naiwny = 2.0;
    double x_stabilny = 2.0;

    for (int k = 1; k < 30; ++k) {
        std::cout << std::left << std::setw(3) << k
                  << std::setw(25) << x_naiwny
                  << std::setw(25) << x_stabilny
                  << std::scientific << std::abs(x_naiwny - PI_REF) << std::fixed << std::endl;

        x_naiwny = ciag_naiwny(x_naiwny, k);
        x_stabilny = ciag_stabilny(x_stabilny, k);
    }
    
    std::cout << std::left << std::setw(3) << 30
              << std::setw(25) << x_naiwny
              << std::setw(25) << x_stabilny
              << std::scientific << std::abs(x_naiwny - PI_REF) << std::fixed << std::endl;

    return 0;
}
