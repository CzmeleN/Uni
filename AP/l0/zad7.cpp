#include <bits/stdc++.h>

using namespace std;

void dfs_tag(vector<bool> &tagged, vector<vector<int>> &g, int x) {
    tagged[x] = true;

    for (int v : g[x]) {
        if (!tagged[v]) {
           dfs_tag(tagged, g, v);
        }
    }
}

int main() {
    int n, m, a, b, res = -1;
    
    cin >> n >> m;

    vector<vector<int>> g(n);
    vector<bool> tagged(n, false);

    for (int i = 0; i < m; ++i) {
        cin >> a >> b;

        --a;
        --b;

        g[a].push_back(b);
        g[b].push_back(a);
    }

    for (int i = 0; i < n; ++i) {
        if (!tagged[i]) {
            dfs_tag(tagged, g, i);
            ++res;
        }
    }

    cout << res << endl;

    return 0;
}
