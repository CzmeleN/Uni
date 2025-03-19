#include <bits/stdc++.h>

using namespace std;
using ull = unsigned long long;

constexpr int N = 200'000;
constexpr int SQRT_N = 500;

ull xs[N];
ull dp[SQRT_N][N];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q, a, b, threshold = 1;
    ull res;

    cin >> n;

    for (int i = 0; i < n; ++i) {
        cin >> xs[i];
    }

    cin >> q;

    while (threshold * threshold < n) threshold++;

    for (int b = 1; b <= threshold; ++b) {
        for (int i = n - 1; i >= 0; --i) {
            if (i + b < n) {
                dp[b][i] = xs[i] + dp[b][i + b];
            } else {
                dp[b][i] = xs[i];
            }
        }
    }

    while (q--) {
        cin >> a >> b;
        a--;

        res = 0;

        if (b <= threshold) {
            res = dp[b][a];
        } else {
            for (int i = a; i < n; i += b) {
                res += xs[i];
            }
        }

        cout << res << '\n';
    }

    return 0;
}
