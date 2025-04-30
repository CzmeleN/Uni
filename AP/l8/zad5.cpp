#include <bits/stdc++.h>

using namespace std;
using ll = long long;

const int N = 200005;

vector<int> adjs[N];
int in[N], out[N], timer = 0;
ll tree[8 * N], vals[N], A[N];

void dfs(int u, int p) {
    in[u] = ++timer;

    for (int v : adjs[u]) {
        if (v == p) continue;
        dfs(v, u);
    }

    out[u] = timer;
}

void build(int p, int l, int r) {
    if (l == r) {
        tree[p] = A[l];
    } else {
        int mid = (l + r) / 2;

        build(p * 2, l, mid);
        build(p * 2 + 1, mid + 1, r);

        tree[p] = tree[p * 2] + tree[p * 2 + 1];
    }
}

void update(int p, int l, int r, int id, ll val) {
    if (l == r) {
        tree[p] = val;
        return;
    }

    int mid = (l + r) / 2;

    if (id <= mid) {
        update(p * 2, l, mid, id, val);
    } else {
        update(p * 2 + 1, mid + 1, r, id, val);
    }

    tree[p] = tree[p * 2] + tree[p * 2 + 1];
}

ll query(int p, int l, int r, int i, int j) {
    if (j < l || r < i) return 0;
    if (i <= l && r <= j) return tree[p];
    
    int mid = (l + r) / 2;

    return query(p * 2, l, mid, i, j) + query(p * 2 + 1, mid + 1, r, i ,j);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, q, u, v;
    ll x;

    cin >> n >> q;

    for (int i = 1; i <= n; ++i) {
        cin >> vals[i];
    }

    for (int i = 0; i < n - 1; ++i) {
        cin >> u >> v;
        adjs[u].push_back(v);
        adjs[v].push_back(u);
    }

    dfs(1, 0);

    for (int i = 1; i <= n; ++i) {
        A[in[i]] = vals[i];
    }

    build(1, 1, n);

    while (q--){
        cin >> u >> v;

        if (u == 1) {
            cin >> x;
            update(1, 1, n, in[v], x);
        } else {
            cout << query(1, 1, n, in[v], out[v]) << '\n';
        }
    }

    return 0;
}
