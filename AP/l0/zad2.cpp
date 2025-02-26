#include <bits/stdc++.h>

typedef unsigned long long int ull;

using namespace std;

constexpr ull MOD = 1000000000;

ull fast_pow(ull x, ull n) {
    ull res = 1;

    while(n) {
        if (n % 2) {
            res *= x;
            res %= MOD;
        }

        x *= x;
        x %= MOD;
        n /= 2;
    }

    return res;
}

int main() {
    ull x, n;

    cin >> x >> n;
    cout << fast_pow(x, n) << endl;
}
