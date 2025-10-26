#include <iostream>
#include <limits>

using namespace std;
using lim_lli = numeric_limits<long long int>;

int main() {
    cout << "min: " << lim_lli::min() << "\nmax: " << lim_lli::max()
        << "\nsigned?: " << lim_lli::is_signed << "\n#bits: " << lim_lli::digits
        << "\n#digits: " << lim_lli::digits10 << endl;

    return 0;
}
