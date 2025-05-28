#include <bits/stdc++.h>

using namespace std;
using ll = long long;

constexpr int N = 1'000'000;

double tab[N];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, sum = 1;
    ll x0, x, y0 = 0, y;
    double last;

    cin >> x0 >> n;

    for (int i = 0; i < n; ++i) {
        cin >> x >> y;

        x -= x0;

        tab[i] = (double)x / (double)y;
    }

    sort(tab, tab + n);
    
    last = tab[0];

    for (int i = 0; i < n; ++i) {
        if (tab[i] != last) sum++;

        last = tab[i];
    }

    cout << sum << '\n';

    return 0;
}
