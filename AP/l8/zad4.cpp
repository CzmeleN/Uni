#include <bits/stdc++.h>

using namespace std;
using ll = long long;

const int N = 200005;

vector<int> adjs[N];
int euler[2 * N], eul_depths[2 * N], first_occ[N], depths[N];
int tree[8 * N], id = 0;

void dfs(int u, int p, int d) {
    depths[u] = d;
    first_occ[u] = id;
    euler[id] = u;
    eul_depths[id] = d;
    id++;

    for (int v : adjs[u]) {
        if (v == p) continue;

        dfs(v, u, d + 1);

        euler[id] = u;
        eul_depths[id] = d;
        id++;
    }
}

void build(int p, int l, int r) {
    if (l == r) {
        tree[p] = l;
    } else {
        int nr, nl, mid = (l + r) / 2;

        build(p * 2, l, mid);
        build(p * 2 + 1, mid + 1, r);

        nl = tree[p * 2];
        nr = tree[p * 2 + 1];

        tree[p] = (eul_depths[nl] < eul_depths[nr] ? nl : nr);
    }
}

int query(int p, int l, int r, int i, int j) {
    if (j < l || r < i) return -1;
    if (i <= l && r <= j) return tree[p];
    
    int mid = (l + r) / 2;
    int nl = query(p * 2, l, mid, i, j);
    int nr = query(p * 2 + 1, mid + 1, r, i ,j);

    if (nl < 0) return nr;
    if (nr < 0) return nl;

    return (eul_depths[nl] < eul_depths[nr] ? nl : nr);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, q, u, v, l, r;

    cin >> n >> q;

    for (int i = 0; i < n - 1; ++i) {
        cin >> u >> v;
        adjs[u].push_back(v);
        adjs[v].push_back(u);
    }

    dfs(1, 0, 0);
    build(1, 0, id - 1);

    while (q--){
        cin >> u >> v;

        l = first_occ[u];
        r = first_occ[v];

        if (l > r) swap(l, r);

        cout << depths[u] + depths[v] - 2 * depths[euler[query(1, 0, id - 1, l, r)]] << '\n';
    }

    return 0;
}
