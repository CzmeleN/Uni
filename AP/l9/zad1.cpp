#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pli = pair<ll, int>;

constexpr ll INF = LONG_LONG_MAX;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, m, u, v, w, to;
    ll dst;
    priority_queue<pli, vector<pli>, greater<pli>> pq;
    pli top;
    pq.push({0,1});

    cin >> n >> m;

    vector<vector<pii>> g(n + 1);
    vector<ll> dist(n + 1, INF);

    dist[1] = 0;

    for (int i = 0; i < m; ++i) {
        cin >> u >> v >> w;
        g[u].push_back({v,w});
    }

    while (!pq.empty()) {
        top = pq.top();
        pq.pop();
        dst = top.first;
        v = top.second;

        if (dst != dist[v]) continue;

        for (const pii &neigh : g[v]) {
            to = neigh.first;
            w = neigh.second;

            if (dist[to] > dst + (ll)w) {
                dist[to] = dst + (ll)w;
                pq.push({dist[to], to});
            }
        }
    }

    for (int i = 1; i <= n; ++i){
        cout << dist[i] << (i == n ? '\n':' ');
    }

    return 0;
}

