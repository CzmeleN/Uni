#include <bits/stdc++.h>

using namespace std;

int dfs_cnt(vector<int> &cnts, vector<vector<int>> &g, int x) {
    int res = 0;

    for (int v : g[x]) {
        res += 1 + dfs_cnt(cnts, g, v);
    }

    cnts[x] = res;

    return res;
}

int main() {
    int n, m, x, res = -1;
    
    cin >> n;

    vector<vector<int>> g(n);
    vector<int> cnts(n);

    for (int i = 1; i < n; ++i) {
        cin >> x;

        g[x - 1].push_back(i);
    }

    dfs_cnt(cnts, g, 0);

    for (int i = 0; i < n; ++i) {
        cout << cnts[i] << ' ';
    }

    cout << endl;

    return 0;
}
