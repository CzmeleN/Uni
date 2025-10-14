#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>

using namespace std;

int main() {
    vector<double> I(21);

    I[0] = log(2026.0 / 2025.0);

    for (int n = 1; n <= 20; ++n) {
        I[n] = (1.0 / n) - 2025.0 * I[n - 1];
    }

    cout << left << setw(5) << "n"
              << setw(25) << "I_n" << endl;

    for (int i = 0; i <= 20; ++i) {
        cout << left << setw(5) << i
                  << scientific << setprecision(15) << setw(25) << I[i]
                  << endl;
    }

    return 0;
}
