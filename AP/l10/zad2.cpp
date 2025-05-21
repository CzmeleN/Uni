#include <bits/stdc++.h>

using namespace std;
using pii = pair<int, int>;

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

    int n, m, u, v, id = 0;

    cin >> n >> m;

    adj = vector<vector<int>>(n + 1);
    radj = vector<vector<int>>(n + 1);
    visited = vector<bool>(n + 1, false);
    label = vector<int>(n + 1, 0);

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

    vector<int> lowest(id + 1, INT_MAX);
    vector<pii> sorted(id);
    vector<int> new_label(id + 1);

    for (int i = 1; i <= n; ++i) {
        lowest[label[i]] = min(lowest[label[i]], i);
    }

    for (int i = 1; i <= id; ++i) {
        sorted[i - 1] = {lowest[i], i};
    }

    sort(sorted.begin(), sorted.end());

    for (int i = 0; i < id; ++i) {
        new_label[sorted[i].second] = i + 1;
    }

    cout << id << '\n';

    for (int i = 1; i <= n; ++i) {
        cout << new_label[label[i]] << (i == n ? '\n' : ' ');
    }

    return 0;
}
