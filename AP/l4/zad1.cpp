#include <bits/stdc++.h>

using namespace std;

constexpr int N = 200'000;
constexpr int LOG_N = 18;

int arr[N];
int st[N][LOG_N];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q, a, b, log_n = 1, len, curr;

    cin >> n >> q;

    for (int i = 0; i < n; ++i) {
        cin >> arr[i];
        st[i][0] = arr[i];
    }

    for (int i = 2; i < n; i <<= 1) log_n++;

    for (int i = 1; i <= log_n; ++i) {
        for (int j = 0; j + (1 << i) <= n; ++j) {
            st[j][i] = min(st[j][i - 1], st[j + (1 << (i - 1))][i - 1]);
        }
    }

    while (q--) {
        cin >> a >> b;
        a--; b--;

        len = b - a + 1;
        log_n = 0;
        
        for (int i = 2; i <= len; i <<= 1) log_n++;

        cout << min(st[a][log_n], st[b - (1 << log_n) + 1][log_n]) << '\n';
    }

    return 0;
}
