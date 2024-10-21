#include <iostream>
#include <cmath>
#include <iomanip>

double f(double x) {
    return 8096.0 * (std::sqrt(std::pow(x, 13) + 4.0) - 2.0) / std::pow(x, 14);
}

double better_f(double x) {
    return 8096.0 / (x * (std::sqrt(std::pow(x, 13) + 4.0) + 2.0));
}

int main() {
    double x_values[] = {1, 1e-1, 1e-2, 1e-3, 1e-4, 1e-5, 1e-6, 1e-7, 1e-8, 1e-9, 1e-10};

    for (const auto x : x_values){
        std::cout << std::fixed << std::setprecision(10);
        std::cout << "f(" << x << ") =\n(oryginalnie): " << f(x) << "\n(poprawione): " << better_f(x) << "\n\n";
    }

    return 0;
}

