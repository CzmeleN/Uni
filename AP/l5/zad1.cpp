#include <bits/stdc++.h>

using namespace std;

constexpr int N = 200'000;

vector<int> adjs[N];

pair<int, int> dfs(int curr, int parent) {
    int best = 0, max1 = -1, max2 = -1, h, through;
    pair<int, int> child;

    for (int v : adjs[curr]) {
        if (v == parent) continue;

        child = dfs(v, curr);
        best = max(best, child.first);

        h = child.second;

        if (h > max1) {
            max2 = max1;
            max1 = h;
        } else if (h > max2) {
            max2 = h;
        }
    }

    h = max1 == -1 ? 0 : max1 + 1;
    through = 0;

    if (max1 != -1) {
        through = (max2 == -1 ? max1 + 1 : max1 + max2 + 2);
    }

    return {max(best, through), h};
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

    cout << dfs(0, 0).first << '\n';

    return 0;
}

