#include <bits/stdc++.h>

using namespace std;
using ll = long long;

constexpr int N = 200'001;

ll A[N];
int tree[4 * N];

void build(int id, int l, int r) {
    if (l == r) {
        tree[id] = 1;
        return;
    }

    int mid = (l + r) / 2;

    build(id * 2, l, mid);
    build(id * 2 + 1, mid + 1, r);

    tree[id] = tree[id * 2] + tree[id * 2 + 1];
}

void update(int id, int l, int r, int pos) {
    if (l == r) {
        tree[id] = 0;
        return;
    }

    int mid = (l + r) / 2;

    if (pos <= mid) {
        update(2 * id, l, mid, pos);
    } else {
        update(2 * id + 1, mid + 1, r, pos);
    }

    tree[id] = tree[2 * id] + tree[2 * id + 1];
}

int n_one(int id, int l, int r, int n) {
    if (l == r) return l;

    int mid = (l + r) / 2;

    if (tree[id * 2] >= n) {
        return n_one(id * 2, l, mid, n);
    } else {
        return n_one(id * 2 + 1, mid + 1, r, n - tree[id * 2]);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, x, id;
    
    cin >> n;

    for (int i = 1; i <= n; ++i) {
        cin >> A[i];
    }

    build(1, 1, n);

    for (int i = 0; i < n; ++i) {
        cin >> x;

        id = n_one(1, 1, n, x);
        cout << A[id] << ' ';

        update(1, 1, n, id);
    }

    cout << '\n';

    return 0;
}

