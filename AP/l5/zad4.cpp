#include <bits/stdc++.h>

using namespace std;
using ll = long long;

constexpr int N = 20;
constexpr ll MOD = 1'000'000'007;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, m, u, v,states, new_m;
    vector<int> adjs[N];

    cin >> n >> m;

    states = 1 << n;
    vector<vector<ll>> dp(states, vector<ll>(n, 0));
    dp[1][0] = 1;

    while (m--) {
        cin >> u >> v;
        u--; v--;
        adjs[u].push_back(v);
    }

    for (int m = 0; m < states; ++m) {
        for (int u = 0; u < n; ++u) {
            if (dp[m][u] == 0) continue;

            for (int v : adjs[u]) {
                if (!(m & (1 << v))) {
                    new_m = m | (1 << v);
                    dp[new_m][v] = (dp[new_m][v] + dp[m][u]) % MOD;
                }
            }
        }
    }

    cout << dp[states - 1][n - 1] << '\n';

    return 0;
}
