#include <string>
#include <iostream>

using ll = long long;

bool is_prime(ll x) {
    if (x <= 1) return false;

    for (ll i = 2; i * i <= x; ++i) {
        if (x % i == 0) return false;
    }

    return true;
}

int main(int argc, char *argv[]) {
    if (argc <= 1) std::clog << "Usage: " << argv[0] << " <number> <number> ...\n";

    for (int i = 1; i < argc; ++i) {
        ll x = std::stoll(argv[i]);

        if (is_prime(x)) std::cout << x << ' ';
    }

    std::cout << '\n';

    return 0;
}
