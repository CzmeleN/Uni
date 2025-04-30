#include <bits/stdc++.h>

using namespace std;
using ll = long long;

const int N = 200005;
const int LOG_N = 18;
int up[N][LOG_N];

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, q, v, k, mid;

    cin >> n >> q;

    up[1][0] = 0;

    for (int i = 2; i <= n; ++i) {
        cin >> up[i][0];
    }

    for(int k = 1; k < LOG_N; ++k){
        for(int i = 1; i <= n; ++i){
            up[i][k] = up[up[i][k - 1]][k - 1];
        }
    }


    while (q--){
        cin >> v >> k;

        for (int i = 0; i < LOG_N && v; ++i){
            if (k & (1 << i)) {
                v = up[v][i];
            }
        }

        cout << (v ? v : -1) << '\n';
    }

    return 0;
}
