#include <bits/stdc++.h>

using namespace std;
using ull = unsigned long long;

constexpr int N = 200'000;
constexpr int SQRT_N = 500;

ull block_sums[SQRT_N] = {0};
ull arr[N];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q, k, block_s = 1, block_c, block_id, type, a, b;
    ull u, res;

    cin >> n >> q;

    for (int i = 0; i < n; ++i) {
        cin >> arr[i];
    }

    while (block_s * block_s < n) block_s++;

    block_c = (n + block_s - 1) / block_s;

    for (int i = 0; i < n; ++i) {
        block_sums[i / block_s] += arr[i];
    }

    while (q--) {
        cin >> type;

        if (type == 1) {
            cin >> k >> u;
            k--;

            block_id = k / block_s;
            block_sums[block_id] = block_sums[block_id] - arr[k] + u;
            arr[k] = u;
        } else {
            cin >> a >> b;
            a--; b--;

            res = 0;

            while (a <= b && a % block_s != 0) res += arr[a++];

            while (a + block_s < b) {
                res += block_sums[a / block_s];
                a += block_s;
            }

            while (a <= b) res += arr[a++];

            cout << res << '\n';
        }
    }

    return 0;
}
