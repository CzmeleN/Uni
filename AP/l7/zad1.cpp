#include <bits/stdc++.h>

using namespace std;
using ll = long long;

constexpr int N = 200'001;

ll A[N];
int tree[4 * N];

void build(int id, int l, int r) {
    if (l == r) {
        tree[id] = A[l];
        return;
    }

    int mid = (l + r) / 2;

    build(id * 2, l, mid);
    build(id * 2 + 1, mid + 1, r);

    tree[id] = max(tree[id * 2], tree[id * 2 + 1]);
}

void update(int id, int l, int r, int pos, ll val) {
    if (l == r) {
        tree[id] -= val;
        return;
    }

    int mid = (l + r) / 2;

    if (pos <= mid) {
        update(2 * id, l, mid, pos, val);
    } else {
        update(2 * id + 1, mid + 1, r, pos, val);
    }

    tree[id] = max(tree[2 * id], tree[2 * id + 1]);
}

int first(int id, int l, int r, ll x) {
    if (tree[id] < x) return 0;

    if (l == r) return l;

    int mid = (l + r) / 2;

    if (tree[id * 2] >= x) {
        return first(id * 2, l, mid, x);
    } else {
        return first(id * 2 + 1, mid + 1, r, x);
    }
}

int query(int id, int l, int r, int ql, int qr) {
    if (qr < l || r < ql) {
        return 0;
    }

    if (ql <= l && r <= qr) {
        return tree[id];
    }

    int mid = (l + r) / 2;

    return query(2 * id, l, mid, ql, qr) + query(2 * id + 1, mid + 1, r, ql, qr);
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, q, id;
    ll x;
    
    cin >> n >> q;

    for (int i = 1; i <= n; ++i) {
        cin >> A[i];
    }

    build(1, 1, n);

    while (q--) {
        cin >> x;

        id = first(1, 1, n, x);
        cout << id << ' ';

        if (id != 0) {
            update(1, 1, n, id, x);
        }
    }

    cout << '\n';

    return 0;
}

