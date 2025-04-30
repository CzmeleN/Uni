#include <bits/stdc++.h>

using namespace std;
using ll = long long;

const int N = 200005;
const int LOG_N = 18;
int up[N][LOG_N], depth[N];

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, q, u, v, diff;

    cin >> n >> q;

    up[1][0] = 0;

    for (int i = 2; i <= n; ++i) {
        cin >> u;

        depth[i] = depth[u] + 1;
        up[i][0] = u;
    }

    for(int k = 1; k < LOG_N; ++k){
        for(int i = 1; i <= n; ++i){
            up[i][k] = up[up[i][k - 1]][k - 1];
        }
    }

    while (q--){
        cin >> u >> v;

        if (depth[u] < depth[v]) {
            swap(u, v);
        }

        diff = depth[u] - depth[v];

        for (int i = 0; i < LOG_N; ++i) {
            if (diff & (1 << i)) {
                u = up[u][i];
            }
        }

        if (u == v) {
            cout << u;
        } else {
            for (int i = LOG_N - 1; i >= 0; --i) {
                if (up[u][i] != up[v][i]) {
                    u = up[u][i];
                    v = up[v][i];
                }
            }

            cout << up[u][0];
        }

        cout << '\n';
    }

    return 0;
}
