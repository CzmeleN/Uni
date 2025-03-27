#include <bits/stdc++.h>

using namespace std;

constexpr int N = 200'000;

struct Query {
    int a, b, id;
};

int arr[N];
int res[N];
pair<int, int> mono[N];
Query queries[N];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q, a, b, mono_s = 0, curr = -1, l, r, m, pos;

    cin >> n >> q;

    for (int i = 0; i < n; ++i) {
        cin >> arr[i];
    }

    for (int i = 0; i < q; ++i) {
        cin >> a >> b;
        queries[i] = {--a, --b, i};
    }

    sort(queries, queries + q, [](const Query &q1, const Query &q2) {
        return q1.b < q2.b;
    });

    for (int i = 0; i < q; ++i) {
        while (curr < queries[i].b) {
            curr++;

            while (mono_s > 0 && mono[mono_s - 1].first > arr[curr]) mono_s--;

            mono[mono_s].first = arr[curr];
            mono[mono_s++].second = curr;
        }

        l = 0;
        r = mono_s - 1;
        pos = -1;

        while (l <= r) {
            m = (l + r) / 2;

            if (mono[m].second >= queries[i].a) {
                pos = m;
                r = m - 1;
            } else {
                l = m + 1;
            }
        }

        res[queries[i].id] = mono[pos].first;
    }

    for (int i = 0; i < q; ++i) {
        cout << res[i] << '\n';
    }

    return 0;
}
