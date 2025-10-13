#include <iostream>
#include <math.h>

using namespace std;

int main() {
    double a, b, c;

    cout << "aX^2 + bX + c" << endl;
    cin >> a >> b >> c;

    if (!a) {
        cout << "non quadratic" << endl;
        return 1;
    }

    if (const auto d = b * b - 4.0 * a * c; d >= 0.0) {
        cout << (-b - sqrt(d)) / (2.0 * a) << endl;

        if (d) cout << (-b + sqrt(d)) / (2.0 * a) << endl;
    } else {
        cout << "function has no zeroes" << endl;
    }

    return 0;
}
