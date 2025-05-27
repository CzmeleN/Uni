#include <bits/stdc++.h>

using namespace std;
using pii = pair<int, int>;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, m, u, v;
    pii curr;

    cin >> n >> m;

    vector<vector<pii>> adj(n + 1);
    vector<int> in_deg(n + 1,0), out_deg(n + 1,0);
    vector<bool> used(m, false);
    vector<int> pos(n + 1,0);
    vector<int> stack, path;

    for (int i = 0; i < m; ++i){
        cin >> u >> v;
        adj[u].emplace_back(v, i);
        out_deg[u]++;
        in_deg[v]++;
    }

    if (out_deg[1] != in_deg[1] + 1 || in_deg[n] != out_deg[n] + 1) {
        cout << "IMPOSSIBLE\n";
        return 0;
    }

    for (int i = 2; i < n; ++i){
        if (in_deg[i] != out_deg[i]){
            cout << "IMPOSSIBLE\n";
            return 0;
        }
    }

    stack.push_back(1);

    while (!stack.empty()) {
        u = stack.back();

        while (pos[u] < adj[u].size() && used[adj[u][pos[u]].second]) pos[u]++;

        if (pos[u] < adj[u].size()) {
            curr = adj[u][pos[u]++];
            used[curr.second] = true;
            stack.push_back(curr.first);
        } else {
            path.push_back(u);
            stack.pop_back();
        }
    }

    if (path.size() != m + 1 || path.front() != n) {
        cout << "IMPOSSIBLE";
    } else {
        for (int i = path.size() - 1; i >= 0; --i) {
            cout << path[i] << ' ';
        }
    }

    cout << '\n';

    return 0;
}
