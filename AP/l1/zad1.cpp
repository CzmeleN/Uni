#include <bits/stdc++.h>

using namespace std;

int ext_gcd(int a, int b, int &k, int &l) {
    if (b == 0) {
        k = 1;
        l = 0;

        return a;
    }

    int k1, l1, d;

    d = ext_gcd(b, a % b, k1, l1);
    k = l1;
    l = k1 - a / b * l1;

    return d;
}

int main() {
    int a, b, k, l, d, n;

    cin >> n;

    while (n--) {
        cin >> a >> b;
        d = ext_gcd(a, b, k, l);
        cout << k << ' ' << l << ' ' << d << endl;
    }
}
