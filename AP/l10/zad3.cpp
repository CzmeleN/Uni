#include <bits/stdc++.h>

using namespace std;
using ll = long long;

vector<vector<int>> adj, radj;
vector<bool> visited;
vector<int> order, label;

void dfs1(int u) {
    visited[u] = true;

    for (int v: adj[u]) {
        if (!visited[v]) dfs1(v);
    }

    order.push_back(u);
}

void dfs2(int u, int id) {
    label[u] = id;

    for (int v : radj[u]) {
        if (label[v] == 0) dfs2(v, id);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, m, u, v, id = 0, l1, l2;
    ll res=  0;
    queue<int> q;

    cin >> n >> m;

    vector<ll> a(n + 1);
    adj = vector<vector<int>>(n + 1);
    radj = vector<vector<int>>(n + 1);
    visited = vector<bool>(n + 1, false);
    label = vector<int>(n + 1, 0);

    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }

    for (int i = 0; i < m; ++i) {
        cin >> u >> v;
        adj[u].push_back(v);
        radj[v].push_back(u);
    }

    for (int i = 1; i <= n; ++i) {
        if (!visited[i]) dfs1(i);
    }

    for (int i = n - 1; i >= 0; --i) {
        u = order[i];

        if (label [u] == 0) dfs2(u, ++id);
    }

    vector<ll> sum(id + 1, 0);
    vector<vector<int>> comp_adj(id + 1);
    vector<int> in_deg(id + 1, 0);

    for (int i = 1; i <= n; ++i) {
        sum[label[i]] += a[i];
    }

    vector<ll> dp = sum;

    for (int i = 1; i <= n; ++i) {
        for (int v : adj[i]) {
            l1 = label[i];
            l2 = label[v];

            if (l1 != l2) {
                comp_adj[l1].push_back(l2);
                in_deg[l2]++;
            }
        }
    }

    for (int i = 1; i <= id; ++i) {
        if (in_deg[i] == 0) q.push(i);
    }

    while (!q.empty()) {
        u = q.front();
        q.pop();
        
        res = max(res, dp[u]);

        for (int v: comp_adj[u]) {
            if (dp[v] < dp[u] + sum[v]) dp[v] = dp[u] + sum[v];
            if (--in_deg[v] == 0) q.push(v);
        }
    }

    cout << res << '\n';
    
    return 0;
}
