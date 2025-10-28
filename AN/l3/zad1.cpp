#include <iostream>
#include <cmath> 
#include <iomanip>

const double PI = std::acos(-1.0);
const double PI_2 = PI / 2.0;

double f_a_naive(double x) {
    double x3 = std::pow(x, 3);
    double x6 = x3 * x3;
    return x3 + std::sqrt(x6 + 2025.0);
}

double f_a_stable(double x) {
    if (x >= 0.0) {
        return f_a_naive(x); 
    } else {
        double x3 = std::pow(x, 3);
        double x6 = x3 * x3;
        return 2025.0 / (std::sqrt(x6 + 2025.0) - x3);
    }
}

double f_b_naive(double x) {
    double acot_x = PI_2 - std::atan(x);
    double numerator = PI_2 - x - acot_x; 
    
    return numerator / std::pow(x, 3);
}

double f_b_stable(double x) {
    double threshold = 1e-4; 

    if (std::fabs(x) > threshold) {
        return (std::atan(x) - x) / std::pow(x, 3);
    } else {
        double x2 = x * x;
        double x4 = x2 * x2;
        return -1.0/3.0 + x2 / 5.0 - x4 / 7.0; 
    }
}


int main() {
    // std::cout << std::fixed << std::setprecision(16);

    std::cout << "(a) x -> -inf\n";
    std::cout << "\tx" << "\t\t\t" << "naiwnie" << "\t\t\t" << "stabilnie" << std::endl;
    
    for (double x = -1e4; x > -1e10; x *= 10) {
        std::cout << "\t" << std::setw(10) << std::scientific << x 
                  << "\t" << std::setw(20) << f_a_naive(x)
                  << "\t" << std::setw(20) << f_a_stable(x) << std::endl;
    }

    std::cout << "(b) x-> 0\n";
    std::cout << "\tx" << "\t\t\t" << "naiwnie" << "\t\t\t" << "stabilnie" << std::endl;

    for (double x = 1e-3; x > 1e-12; x /= 10) {
         std::cout << "\t" << std::setw(10) << x 
                  << "\t" << std::setw(20) << f_b_naive(x)
                  << "\t" << std::setw(20) << f_b_stable(x) << std::endl;
    }

    return 0;
}
