#include <bits/stdc++.h>

using namespace std;

constexpr int N = 200'000;

vector<int> adjs[N];
int dp_free[N];
int dp_taken[N];

void dfs(int curr, int parent) {
    int sum = 0;

    for (int v : adjs[curr]) {
        if (v == parent) continue;

        dfs(v, curr);

        sum += dp_free[v];
    }

    dp_taken[curr] = sum;
    dp_free[curr] = sum;

    for (int v : adjs[curr]) {
        if (v == parent) continue;
        
        dp_free[curr] = max(dp_free[curr], sum - dp_free[v] + dp_taken[v] + 1);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, a, b;

    cin >> n;

    while (--n) {
        cin >> a >> b;
        a--; b--;

        adjs[a].push_back(b);
        adjs[b].push_back(a);
    }

    dfs(0, 0);

    cout << dp_free[0] << '\n';

    return 0;
}
