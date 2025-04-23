#include <bits/stdc++.h>

using namespace std;
using ll = long long;

constexpr int M = 1'000'001;

int tree[4 * M] = {0};

void update(int id, int l, int r, int pos, int val) {
    if (l == r) {
        tree[id] += val;
        return;
    }

    int mid = (l + r) / 2;

    if (pos <= mid) {
        update(2 * id, l, mid, pos, val);
    } else {
        update(2 * id + 1, mid + 1, r, pos, val);
    }

    tree[id] = tree[2 * id] + tree[2 * id + 1];
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

    int n, x;
    ll res = 0;
    
    cin >> n;

    while (n--) {
        cin >> x;

        res += query(1, 0, M - 1, x + 1, M - 1);
        update(1, 0, M - 1, x, 1);
    }

    cout << res << '\n';

    return 0;
}

