#include <bits/stdc++.h>

using namespace std;

using ll = long long;
const ll INF = LONG_LONG_MAX;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, m, q, u, v;
    ll w;

    cin >> n >> m >> q;

    vector<vector<ll>> dist(n + 1, vector<ll>(n + 1, INF));

    for (int i = 1; i <= n; ++i) dist[i][i]= 0;

    for (int i = 0; i < m; ++i){
        cin >> u >> v >> w;

        if (w < dist[u][v]) {
            dist[u][v] = w;
            dist[v][u] = w;
        }
    }

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (dist[j][i] != INF) {
                for (int k = 1; k <= n; ++k) {
                    if (dist[i][k] != INF && dist[j][k] > dist[j][i] + dist[i][k]) {
                        dist[j][k] = dist[j][i] + dist[i][k];
                    }
                }
            }
        }
    }

    while (q--){
        cin >> u >> v;
        cout << (dist[u][v] == INF ? -1 : dist[u][v]) << '\n';
    }

    return 0;
}

