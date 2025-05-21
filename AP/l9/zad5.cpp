#include <bits/stdc++.h>

using namespace std;
using ll = long long;

constexpr ll INF = LONG_LONG_MAX;

struct Edge {
    int u, v;
    ll w;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, m, u, v;
    ll w;
    bool upd;

    cin >> n >> m;

    vector<Edge> edges(m);
    vector<vector<int>> adj(n+1), radj(n+1);
    vector<bool> reach1(n+1, 0);
    vector<char> reach_n(n+1, 0);
    vector<ll> dist(n+1, INF);
    queue<int> q;

    for (int i = 0; i < m; i++) {
        cin >> u >> v >> w;

        edges[i] = {u, v, -w};
        adj[u].push_back(v);
        radj[v].push_back(u);
    }

    reach1[1] = true;
    q.push(1);

    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v : adj[u]) {
            if (!reach1[v]) {
                reach1[v] = true;
                q.push(v);
            }
        }
    }

    reach_n[n] = true;
    q.push(n);

    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v : radj[u]) {
            if (!reach_n[v]) {
                reach_n[v] = true;
                q.push(v);
            }
        }
    }

    dist[1] = 0;

    for (int it = 1; it < n; it++) {
        upd = false;

        for (auto &e : edges) {
            if (!reach1[e.u] || !reach_n[e.v]) continue;

            if (dist[e.u] != INF && dist[e.v] > dist[e.u] + e.w) {
                dist[e.v] = dist[e.u] + e.w;
                upd = true;
            }
        }

        if (!upd) break;
    }

    for (auto &e : edges) {
        if (!reach1[e.u] || !reach_n[e.v]) continue;

        if (dist[e.u] != INF && dist[e.v] > dist[e.u] + e.w) {
            cout << -1 << '\n';
            return 0;
        }
    }

    cout << -dist[n] << '\n';

    return 0;
}

