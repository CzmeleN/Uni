#include <bits/stdc++.h>

typedef long long int ll;

using namespace std;

ll gdc(ll a, ll b) {
    ll x;

    while (b != 0) {
        x = a % b;
        a = b;
        b = x;
    }

    return a;
}

int main() {
    ll a, b;

    cin >> a >> b;
    cout << gcd(a, b) << endl;
}
