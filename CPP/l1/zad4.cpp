#include <cstdint>
#include <iostream>
#include <stdint.h>

using namespace std;

auto nth_lucas(uint64_t n) {
    if (n == 0) return uint64_t {2};
    else if (n == 1) return uint64_t {1};
    
    return nth_lucas(n - 1) + nth_lucas(n - 2);
}

int main() {
    uint64_t nrs[] = {0, 1, 5, 15};

    for (const auto& nr: nrs) {
        cout << nth_lucas(nr) << endl;
    }

    return 0;
}
