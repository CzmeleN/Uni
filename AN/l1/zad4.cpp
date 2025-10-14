#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>

using namespace std;

int main() {
    vector<double> y(51);

    y[0] = 1.0;
    y[1] = -1.0 / 9.0;

    for (int n = 0; n <= 48; ++n) {
        y[n + 2] = (98.0 / 9.0) * y[n + 1] + (11.0 / 9.0) * y[n];
    }

    cout << left << setw(5) << "n"
              << setw(25) << "calculated y_n"
              << setw(25) << "real y_n" << endl;

    for (int i = 0; i <= 50; ++i) {
        double true_val = pow(-1.0 / 9.0, i);

        cout << left << setw(5) << i
                  << scientific << setprecision(15) << setw(25) << y[i]
                  << setw(25) << true_val << endl;
    }

    return 0;
}
