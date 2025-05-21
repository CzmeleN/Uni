#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, m, u, v;
    priority_queue<int, vector<int>, greater<int>> pq;

    cin >> n >> m;

    vector<vector<int>> adj(n + 1);
    vector<int> in_deg(n + 1, 0);
    vector<int> topo;

    for (int i = 0; i < m; ++i) {
        cin >> u >> v;
        adj[u].push_back(v);
        in_deg[v]++;
    }

    for (int i = 1; i <= n; ++i) {
        if (in_deg[i] == 0) pq.push(i);
    }

    while (!pq.empty()) {
        u = pq.top();
        pq.pop();

        topo.push_back(u);

        for (int v: adj[u]) {
            if (--in_deg[v] == 0) pq.push(v);
        }
    }

    if (topo.size() < n) {
        cout << "IMPOSSIBLE\n";
    } else {
        for (int i = 0; i < n; ++i) {
            cout << topo[i] << (i == n - 1 ? '\n' : ' ');
        }
    }

    return 0;
}
