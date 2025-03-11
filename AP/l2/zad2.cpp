#include <bits/stdc++.h>
#include <unordered_set>

using namespace std;

constexpr int N = 200'000;

int colors[N];
vector<int> tree[N];
int res[N];
unordered_set<int> sets[N];

void dfs(int v, int prev) {
    sets[v].insert(colors[v]);

    for (int child : tree[v]) {
        if (child == prev) continue;

        dfs(child, v);

        if (sets[v].size() < sets[child].size()) {
            swap(sets[v], sets[child]);
        }

        for (int col : sets[child]) {
            sets[v].insert(col);
        }
    }

    res[v] = sets[v].size();
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, u, v;
    cin >> n;

    for (int i = 0; i < n; ++i) {
        cin >> colors[i];
    }

    for (int i = 1; i < n; ++i) {
        cin >> u >> v;

        u--;
        v--;

        tree[u].push_back(v);
        tree[v].push_back(u);
    }

    dfs(0, -1);

    for (int i = 0; i < n; ++i) {
        cout << res[i] << ' ';
    }

    cout << '\n';

    return 0;
}
