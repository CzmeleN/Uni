#include <bits/stdc++.h>

using namespace std;
using ll = long long;

constexpr int N = 60'001;

ll tree[4 * N], lazy[4 * N];

void push(int id) {
    if (lazy[id]) {
        ll val = lazy[id];
        
        lazy[id * 2] += val;
        lazy[id * 2 + 1] += val;
        tree[id * 2] += val;
        tree[id * 2 + 1] += val;
        lazy[id] = 0;
    }
}

void build(int id, int l, int r, int m) {
    lazy[id] = 0;

    if (l == r) {
        tree[id] = m;
        return;
    }

    int mid = (l + r) / 2;

    build(id * 2, l, mid, m);
    build(id * 2 + 1, mid + 1, r, m);

    tree[id] = min(tree[id * 2], tree[id * 2 + 1]);
}

void update(int id, int l, int r, int ql, int qr, ll val) {
    if (qr < l || r < ql) return;

    if (ql <= l && r <= qr) {
        tree[id] -= val;
        lazy[id] -= val;
        return;
    }

    push(id);

    int mid = (l + r) / 2;

    update(2 * id, l, mid, ql, qr, val);
    update(2 * id + 1, mid + 1, r, ql, qr, val);

    tree[id] = min(tree[2 * id], tree[2 * id + 1]);
}

ll query(int id, int l, int r, int ql, int qr) {
    if (qr < l || r < ql) return LONG_LONG_MAX;

    if (ql <= l && r <= qr) return tree[id];

    push(id);

    int mid = (l + r) / 2;

    return min(query(id * 2, l, mid, ql, qr), query(id * 2 + 1, mid + 1, r, ql, qr));
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, m, q, p, k;
    ll l;
    
    cin >> n >> m >> q;

    build(1, 1, n - 1, m);

    while (q--) {
        cin >> p >> k >> l;

        m = query(1, 1, n - 1, p, k - 1);

        if (m >= l) {
            cout << "T\n";
            update(1, 1, n - 1, p, k - 1, l);
        } else {
            cout << "N\n";
        }
    }

    return 0;
}

