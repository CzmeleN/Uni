#include <bits/stdc++.h>

using namespace std;

constexpr int N = 100'000;

int parents[N];
int sizes[N];
int comp_mins[N];
int comp_maxes[N];
int edge_counts[N];

int find(int x) {
    if (parents[x] != x) {
        parents[x] = find(parents[x]);
    }

    return parents[x];
}

void union_sets(int a, int b) {
    a = find(a);
    b = find(b);

    if (a == b) {
        edge_counts[a]++;
        return;
    }

    if (sizes[a] < sizes[b]) swap(a, b);

    parents[b] = a;
    sizes[a] += sizes[b];
    comp_mins[a] = min(comp_mins[a], comp_mins[b]);
    comp_maxes[a] = max(comp_maxes[a], comp_maxes[b]);
    edge_counts[a] += edge_counts[b] + 1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, u, v, prev_u, prev_v, res;

    cin >> n >> m;

    for (int i = 0; i < n; ++i) {
        parents[i] = i;
        sizes[i] = 1;
        comp_mins[i] = i + 1;
        comp_maxes[i] = i + 1;
        edge_counts[i] = 0;
    }

    while (m--) {
        cin >> u >> v;

        u--;
        v--;

        u = find(u);
        v = find(v);

        if (u == v) {
            edge_counts[u]++;
        } else {
            union_sets(u, v);
            u = find(u);
        }

        cout << (comp_maxes[u] - comp_mins[u]) * (long long)edge_counts[u] << '\n';
    }

    return 0;
}
