#include <bits/stdc++.h>

using namespace std;
using pii = pair<int, int>;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, m, u, v;
    pii curr;

    cin >> n >> m;

    vector<vector<pii>> adj(n + 1);
    vector<int> deg(n + 1,0);
    vector<bool> used(m, false);
    vector<int> pos(n + 1,0);
    vector<int> stack, cycle;

    for (int i = 0; i < m; ++i){
        cin >> u >> v;
        adj[u].emplace_back(v, i);
        adj[v].emplace_back(u, i);
        deg[u]++;
        deg[v]++;
    }

    for (int i = 1; i <= n; ++i){
        if (deg[i] % 2 == 1){
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
            cycle.push_back(u);
            stack.pop_back();
        }
    }

    if (cycle.size() != m + 1) {
        cout << "IMPOSSIBLE";
    } else {
        for (int i = 0; i < cycle.size(); ++i) {
            cout << cycle[i] << ' ';
        }
    }

    cout << '\n';

    return 0;
}
