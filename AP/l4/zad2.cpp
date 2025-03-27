#include <bits/stdc++.h>

using namespace std;

constexpr int N = 200'000;

struct Query {
    int l, r, id;
};

int arr[N];
int res[N];
vector<Query> queries;

void divide(int l, int r, vector<Query>& queries) {
    if (queries.empty()) return;

    if (l == r) {
        for (auto &q : queries) {
            res[q.id] = arr[l];
        }
        return;
    }

    int m = (l + r) / 2;
    vector<Query> l_qs, r_qs;
    vector<int> suf(m - l + 1), pref(r - m);
    int l_min, r_min;

    suf[m - l] = arr[m];
    for (int i = m - 1; i >= l; --i) {
        suf[i - l] = min(arr[i], suf[i - l + 1]);
    }

    pref[0] = arr[m + 1];
    for (int i = m + 2; i <= r; ++i) {
        pref[i - m - 1] = min(arr[i], pref[i - m - 2]);
    }

    for (auto &q : queries) {
        if (q.r <= m) {
            l_qs.push_back(q);
        } else if (q.l > m) {
            r_qs.push_back(q);
        } else {
            res[q.id] = min(suf[q.l - l], pref[q.r - m - 1]);
        }
    }

    divide(l, m, l_qs);
    divide(m + 1, r, r_qs);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q, a, b, log_n = 1, len, curr;

    cin >> n >> q;

    queries.resize(q);

    for (int i = 0; i < n; ++i) {
        cin >> arr[i];
    }

    for (int i = 0; i < q; ++i) {
        cin >> a >> b;
        queries[i] = {--a, --b, i};
    }

    divide(0, n - 1, queries);

    for (int i = 0; i < q; ++i) {
        cout << res[i] << '\n';
    }

    return 0;
}
