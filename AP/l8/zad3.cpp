#include <bits/stdc++.h>

using namespace std;
using ll = long long;

const int N = 200005;
const int LOG_N = 18;
int up[N][LOG_N], depth[N], parent[N];
ll diff[N], res[N];
vector<int> adjs[N];

void dfs_pre(int u, int p) {
    parent[u] = p;
    depth[u] = depth[p] + 1;
    up[u][0] = p;

    for (int v : adjs[u]) {
        if (v == p) continue;
        dfs_pre(v, u);
    }
}

ll dfs(int u, int p) {
    ll r = diff[u];

    for (int v : adjs[u]) {
        if (v == p) continue;
        r += dfs(v, u);
    }

    res[u] = r;

    return r;
}

int lca(int u, int v) {
    if (depth[u] < depth[v]) swap(u, v);

    int diff = depth[u] - depth[v];

    for (int i = 0; i < LOG_N; ++i) {
        if (diff & (1 << i)) {
            u = up[u][i];
        }
    }

    if (u == v) return u;

    for (int i = LOG_N - 1; i >= 0; --i) {
        if (up[u][i] != up[v][i]) {
            u = up[u][i];
            v = up[v][i];
        }
    }

    return up[u][0];
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, m, u, v, id;

    cin >> n >> m;

    for(int i = 0, u, v; i < n-1; ++i){
        cin >> u >> v;
        adjs[u].push_back(v);
        adjs[v].push_back(u);
    }

    depth[0]  = -1;
    dfs_pre(1, 0);

    for(int k = 1; k < LOG_N; ++k){
        for(int i = 1; i <= n; ++i){
            up[i][k] = up[up[i][k - 1]][k - 1];
        }
    }

    for (int i = 0; i < m; ++i){
        cin >> u >> v;

        id = lca(u, v);

        diff[u] += 1;
        diff[v] += 1;
        diff[id] -= 1;

        if(parent[id]) {
            diff[parent[id]] -= 1;
        }
    }

    dfs(1, 0);

    for(int i = 1; i <= n; ++i){
        cout << res[i] << ' ';
    }

    cout << '\n';

    return 0;
}


