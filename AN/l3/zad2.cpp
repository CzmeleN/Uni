#include <ios>
#include <iostream>
#include <cmath>
#include <iomanip>
#include <utility>

std::pair<double, double> solve_naive(double a, double b, double c) {
    double delta = b * b - 4 * a * c;
    if (delta < 0) return {NAN, NAN};
    
    double sqrt_delta = std::sqrt(delta);
    
    double x1 = (-b + sqrt_delta) / (2 * a);
    double x2 = (-b - sqrt_delta) / (2 * a);
    
    return {x1, x2};
}

std::pair<double, double> solve_stable(double a, double b, double c) {
    double delta = b * b - 4 * a * c;
    if (delta < 0) return {NAN, NAN};

    double sqrt_delta = std::sqrt(delta);
    double q = -b - std::copysign(1.0, b) * sqrt_delta;
    double x1 = q / (2 * a);
    double x2;

    if (x1 == 0.0) {
        x2 = -b / a;
    } else {
        x2 = c / (a * x1);
    }
    
    return {x1, x2};
}

int main() {
    // std::cout << std::fixed << std::setprecision(15);
    std::cout << std::scientific;

    double a = 1.0;
    double b = 1e9; 
    double c = 1.0;

    std::cout << "a=1, b=1e9, c=1" << std::endl;
    
    std::pair<double, double> roots_naive = solve_naive(a, b, c);
    std::cout << "naiwnie: " << std::endl;
    std::cout << "\tx1 (-b + ...): " << roots_naive.first << std::endl;
    std::cout << "\tx2 (-b - ...): " << roots_naive.second << std::endl;

    std::cout << std::endl;

    std::pair<double, double> roots_stable = solve_stable(a, b, c);
    std::cout << "stabilnie:" << std::endl;
    std::cout << "\tx1 (stabilny): " << roots_stable.first << std::endl;
    std::cout << "\tx2 (z Viety):  " << roots_stable.second << std::endl;

    return 0;
}
