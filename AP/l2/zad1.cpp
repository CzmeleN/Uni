#include <bits/stdc++.h>

using namespace std;

constexpr int K = 12;

int ps[K];
int as[K];

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

int inv(int a, int mod) {
    int x, y, d = ext_gcd(a, mod, x, y);

    x %= mod;

    return x < 0 ? x + mod : x;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long k, n, p, res, m, minv;

    cin >> n;

    while (n--) {
        cin >> k;

        p = 1;
        res = 0;

        for (int i = 0; i < k; ++i) {
            cin >> ps[i] >> as[i];
            p *= ps[i];
        }

        for (int i = 0; i < k; ++i) {
            m = p / ps[i];
            minv = inv(m % ps[i], ps[i]);
            res = (res + as[i] * m % p * minv) % p;
        }

        cout << res << '\n';
    }

    return 0;
}
