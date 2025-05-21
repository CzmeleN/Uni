#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pli = pair<ll, int>;

constexpr ll INF = LONG_LONG_MAX;
constexpr int N = 2501;
constexpr int M = 5001;

struct Edge {
    int u;
    int v;
    ll w;
};

ll dists[N];
int cycle[N];
int par[N];
Edge edges[M];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, m, u, v, x, len = 0;
    ll dst, w;
    pli top;

    cin >> n >> m;

    for (int i = 0; i < m; ++i) {
        cin >> edges[i].u >> edges[i].v >> edges[i].w;
    }

    for (int i = 0; i <= n; ++i) {
        par[i] = -1;
    }

    for (int i = 0; i < n; ++i) {
        x = -1;

        for (int j = 0; j < m; ++j) {
            u = edges[j].u;
            v = edges[j].v;
            w = edges[j].w;

            if (dists[v] > dists[u] + w) {
                dists[v] = dists[u] + w;
                par[v] = u;
                x = v;
            }
        }
    }

    if (x == -1) {
        cout << "NO\n";
        return 0;
    }

    for (int i = 0; i < n; ++i) {
        x = par[x];
    }

    v = x;

    cout << "YES\n";

    while (true) {
        cycle[len++] = v;
        
        if (v == x && len > 1) break;

        v = par[v];
    }

    for (int i = len - 1; i >= 0; --i) {
        cout << cycle[i] << (i == 0 ? '\n' : ' ');
    }

    return 0;
}

