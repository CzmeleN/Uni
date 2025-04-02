#include <bits/stdc++.h>

using namespace std;

constexpr int N = 20;

int profit[N][N];
int dp[1 << N] = {0};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, states, x, new_m;
    
    cin >> n;

    states = 1 << n;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> profit[i][j];
        }
    }

    for (int m = 0; m < states; ++m) {
        x = __builtin_popcount(m);

        for (int i = 0; i < n; ++i) {
            if (!(m & (1 << i))) {
                new_m = m | (1 << i);
                dp[new_m] = max(dp[new_m], dp[m] + profit[x][i]);
            }
        }
    }

    cout << dp[states - 1] << '\n';

    return 0;
}
