#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int q;
    ll x1, x2, y1, y2, x3, y3;
    ll nx2, nx3, ny2, ny3, w;

    cin >> q;

    while (q--) {
        cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;

        nx2 = x2 - x1;
        nx3 = x3 - x1;
        ny2 = y2 - y1;
        ny3 = y3 - y1;

        w = nx2 * ny3 - nx3 * ny2;

        cout << fixed << setprecision(9) << abs(w) / sqrt((nx2 * nx2 + ny2 * ny2)) << '\n';
    }

    return 0;
}
