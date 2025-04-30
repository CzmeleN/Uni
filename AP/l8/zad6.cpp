#include <bits/stdc++.h>

using namespace std;
using ll = long long;

const int N = 200005;

vector<int> adjs[N];
int in[N], out[N], timer = 0;
ll tree[8 * N] = {0}, vals[N], lazy[8 * N] = {0};

void dfs(int u, int p) {
    in[u] = ++timer;

    for (int v : adjs[u]) {
        if (v == p) continue;
        dfs(v, u);
    }

    out[u] = timer;
}

void push(int id) {
    if (lazy[id]) {
        ll d = lazy[id];

        tree[id * 2] += d;
        tree[id * 2 + 1] += d;
        lazy[id * 2] += d;
        lazy[id * 2 + 1] += d;
        lazy[id] = 0;
    }
}

void update(int id, int l, int r, int ql, int qr, ll val) {
    if(qr < l || r < ql) return;

    if(ql <= l && r <= qr){
        tree[id] += val;
        lazy[id] += val;
        return;
    }

    push(id);

    int mid = (l + r) / 2;

    update(id * 2, l, mid, ql, qr, val);
    update(id * 2 + 1, mid+1, r,  ql, qr, val);
}

ll query(int p, int l, int r, int pos) {
    if (l == r) return tree[p];

    push(p);
    
    int mid = (l + r) / 2;

    if (pos <= mid) {
        return query(p * 2, l,  mid, pos);
    } else {
        return query(p * 2 + 1, mid + 1, r, pos);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, q, u, v;
    ll x, d;

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
        update(1, 1, timer, in[i], out[i], vals[i]);
    }

    while (q--){
        cin >> u >> v;

        if (u == 1) {
            cin >> x;

            d = x - vals[v];
            vals[v] = x;

            update(1, 1, timer, in[v], out[v], d);
        } else {
            cout << query(1, 1, timer, in[v]) << '\n';
        }
    }

    return 0;
}
