#include <bits/stdc++.h>

using namespace std;

constexpr int N = 10'001;

struct triplet {
    int l;
    int m;
    int r;
};

struct vertex {
    int m;
    int r;
    bool visited;
};

vector<vertex> graph[N];
vector<triplet> path;

bool dfs(int c) {
    for (auto &v : graph[c]) {
        if (v.r == 0) {
            path.push_back({c, v.m, v.r});
            return true;
        }

        if (v.visited) continue;

        v.visited = true;

        if (dfs(v.r)) {
            path.push_back({c, v.m, v.r});
            return true;
        }
    }

    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, l, m, r;
    triplet t;

    cin >> n;

    while(n--) {
        cin >> l >> m >> r;

        graph[l].push_back({m, r, false});
    }

    if (dfs(0)) {
        cout << path.size() << '\n';

        while (path.size()) {
            t = path.back();
            path.pop_back();
            cout << t.l << ' ' << t.m << ' ' << t.r << '\n';
        }
    } else {
        cout << "BRAK\n";
    }

    return 0;
}
