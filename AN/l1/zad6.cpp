#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

int main() {
    const long long N = 2000000;
    
    double sum = 0.0;

    for (long long k = 0; k < N; ++k) {
        double term = 1.0 / (2.0 * k + 1.0);
        if (k % 2 == 0) {
            sum += term;
        } else {
            sum -= term;
        }
    }

    double pi_approx = 4.0 * sum;

    const double PI_TRUE = 3.14159265358979323846;

    double error = abs(PI_TRUE - pi_approx);

    cout << fixed << setprecision(15);
    cout << "term count: " << N << endl;
    cout << "approx PI:  " << pi_approx << endl;
    cout << "real PI:    " << PI_TRUE << endl;
    cout << "error:      " << error << endl;

    return 0;
}
