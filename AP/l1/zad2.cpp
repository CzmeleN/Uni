#include <bits/stdc++.h>

typedef long long int ll;

using namespace std;

constexpr ll MOD = 1'000'000'007;
constexpr int N = 1'000'001;

ll fact[N];

void precomp() {
    ll x = 1;

    fact[0] = 1;

    for (int i = 1; i < N;) {
        fact[i] = x;

        x *= ++i;
        x %= MOD;
    }
}

ll fast_pow(ll x, ll n) {
    ll res = 1;

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
    ll n, a, b, den;

    precomp();

    cin >> n;

    while (n--) {
        cin >> a >> b;

        den = fact[b] * fact[a - b];
        den %= MOD;

        cout << (fact[a] * fast_pow(den, MOD - 2)) % MOD << endl;
    }
}
