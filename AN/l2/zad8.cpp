#include <iostream>
#include <cmath>
#include <iomanip>

double compute_fx_taylor(double x) {
    const double threshold = 1e-5;
    const double f_limit = 2024.0;
    
    if (x < threshold) {
        return 2024.0 - 806.4 * x * x + 77.0 * x * x * x * x;
    } else {
        return 1518.0 * (2.0 * x - sin(2.0 * x)) / (x * x * x);
    }
}

int main() {
    std::cout << std::fixed << std::setprecision(15);
    
    for(int i = 11; i <= 20; ++i) {
        double x = pow(10.0, -static_cast<double>(i));
        double fx = compute_fx_taylor(x);
        
        std::cout << "i = " << i 
                  << ", x = " << x 
                  << ", f(x) = " << fx << std::endl;
    }
    
    return 0;
}


