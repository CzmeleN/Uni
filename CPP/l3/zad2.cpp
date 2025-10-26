#include <iostream>
#include <limits>

using namespace std;
using lim_ld = numeric_limits<long double>;

int main() {
    cout << "smallest > 0: " << lim_ld::min() << "\nmax: " << lim_ld::max()
        << "\nhas inf?: " << lim_ld::has_infinity << "\n1 - (min > 1): "
        << lim_ld::epsilon() << endl;

    return 0;
}
