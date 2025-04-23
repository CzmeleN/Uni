#include <bits/stdc++.h>

using namespace std;
using ll = long long;

constexpr int N = 200'001;

ll A[N];
ll tree[4 * N] = {0};

void update(int id, int l, int r, int ql, int qr, ll val) {
    if (qr < l || r < ql) return;

    if (ql <= l && r <= qr) {
        tree[id] += val;
        return;
    }

    int mid = (l + r) / 2;

    update(2 * id, l, mid, ql, qr, val);
    update(2 * id + 1, mid + 1, r, ql, qr, val);
}

ll query(int id, int l, int r, int pos) {
    if (l == r) {
        return A[pos] + tree[id];
    }

    int mid = (l + r) / 2;

    return tree[id] + (pos <= mid ? query(2 * id, l, mid, pos) : query(2 * id + 1, mid + 1, r, pos));
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, q, x, y, type;
    ll v;
    
    cin >> n >> q;

    for (int i = 1; i <= n; ++i) {
        cin >> A[i];
    }

    while (q--) {
        cin >> type;

        if (type == 1) {
            cin >> x >> y >> v;
            update(1, 1, n, x, y, v);
        } else {
            cin >> x;
            cout << query(1, 1, n, x) << '\n';
        }

    }

    return 0;
}

