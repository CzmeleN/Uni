#include <bits/stdc++.h>

using namespace std;

constexpr int N = 100'000;

int parents[N];
int sizes[N];
int components;
int max_size = 1;

int find(int x) {
    if (parents[x] != x) {
        parents[x] = find(parents[x]);
    }

    return parents[x];
}

void union_sets(int a, int b) {
    a = find(a);
    b = find(b);

    if (a == b) return;

    if (sizes[a] < sizes[b]) swap(a, b);

    parents[b] = a;
    sizes[a] += sizes[b];
    components--;

    if (sizes[a] > max_size) {
        max_size = sizes[a];
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, u, v;

    cin >> n >> m;

    for (int i = 0; i < n; ++i) {
        parents[i] = i;
        sizes[i] = 1;
    }

    components = n;

    while (m--) {
        cin >> u >> v;

        u--;
        v--;

        union_sets(u, v);

        cout << components << ' ' << max_size << '\n';
    }

    return 0;
}
