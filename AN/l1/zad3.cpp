#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

int main() {
    cout << left << setw(4) << "i"
              << setw(22) << "float"
              << setw(22) << "double" << endl;

    for (int i = 1; i <= 20; ++i) {
        double x_d = pow(10.0, -i);
        float x_f = static_cast<float>(x_d);
        float result_f = 162.0f * (1.0f - cos(5.0f * x_f)) / (x_f * x_f);
        double result_d = 162.0 * (1.0 - cos(5.0 * x_d)) / (x_d * x_d);

        cout << left << setw(4) << i
                  << fixed << setprecision(10) << setw(22) << result_f
                  << setw(22) << result_d << endl;
    }

    return 0;
}
