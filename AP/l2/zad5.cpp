#include <bits/stdc++.h>

using namespace std;

constexpr int N = 1'000'000;

int parents[N];
int ranks[N];
int parities[N];

int find(int x) {
    int root;

    if (parents[x] != x) {
        root = find(parents[x]);
        parities[x] ^= parities[parents[x]];
        parents[x] = root;
    }

    return parents[x];
}

bool union_sets(int a, int b, int v) {
    int ra, rb;

    ra = find(a);
    rb = find(b);

    if (ra == rb) {
        return ((parities[a] ^ parities[b]) == v);
    }

    if (ranks[ra] < ranks[rb]) swap(ra, rb);

    parents[rb] = ra;
    parities[rb] = parities[a] ^ parities[b] ^ v;

    if (ranks[ra] == ranks[rb]) {
        ranks[ra]++;
    }

    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, a, b, p, res;

    cin >> n >> m;

    for (int i = 0; i < n; ++i) {
        parents[i] = i;
        ranks[i] = 0;
        parities[i] = 0;
    }

    res = m;

    for (int i = 0; i < m; ++i) {
        cin >> a >> b >> p;

        a--;
        b--;

        if (!union_sets(a, b, p)) {
            res = i;

            for (int j = i + 1; j < m; ++j) {
                cin >> a >> b >> p;
            }

            cout << res << '\n';
            return 0;
        }

    }

    cout << m << '\n';

    return 0;
}
