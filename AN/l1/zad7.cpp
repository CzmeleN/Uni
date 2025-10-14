#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>

using namespace std;

const double PI = 3.14159265358979323846;

double my_cos(double x) {
    double sign = 1.0;

    x = abs(x);

    if (x > PI / 2.0) {
        x = PI - x;
        sign = -1.0;
    }

    double x_squared = x * x;
    double current_sum = 1.0;
    double term = 1.0;

    for (int k = 1; k < 100; ++k) {
        term = term * (-x_squared) / ((2.0 * k) * (2.0 * k - 1.0));

        double old_sum = current_sum;
        current_sum += term;

        if (current_sum == old_sum) {
            break;
        }
    }

    return sign * current_sum;
}

int main() {
    cout << left << setw(15) << "x (rad)"
              << setw(25) << "my_cos(x)"
              << setw(25) << "cos(x)"
              << setw(20) << "diff" << endl;

    vector<double> test_values = {
        0.0, PI / 6.0, PI / 4.0, PI / 3.0, PI / 2.0,
        2.0 * PI / 3.0, PI, -PI / 3.0, -PI
    };

    for (double val : test_values) {
        double my_val = my_cos(val);
        double lib_val = cos(val);
        double diff = abs(my_val - lib_val);

        cout << fixed << setprecision(6) << setw(15) << val
                  << setprecision(18) << setw(25) << my_val
                  << setw(25) << lib_val
                  << scientific << setprecision(2) << diff << endl;
    }

    return 0;
}
