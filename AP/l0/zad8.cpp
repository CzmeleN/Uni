#include <bits/stdc++.h>

using namespace std;

constexpr int N = 100000;

int main() {
    int n, m, a, b;
    queue<int> q;
    
    cin >> n >> m;

    vector<vector<int>> g(n);
    vector<int> dists(n, -1);

    for (int i = 0; i < m; ++i) {
        cin >> a >> b;

        --a;
        --b;

        g[a].push_back(b);
        g[b].push_back(a);
    }

    dists[0] = 0;
    q.push(0);

    while (!q.empty()) {
        a = q.front();
        q.pop();

        for (int x : g[a]) {
            if (dists[x] == -1) {
                dists[x] = dists[a] + 1;
                q.push(x);
            }
        }
    }

    for (int i = 1; i < n; ++i) {
        cout << dists[i] << ' ';
    }

    cout << endl;

    return 0;
}
