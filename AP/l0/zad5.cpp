#include <bits/stdc++.h>

using namespace std;

constexpr int N = 12;

bool col[N] = {0};
bool diag1[2 * N] = {0};
bool diag2[2 * N] = {0};

int backtrack(int n, int x) {
    int res = 0;

    for (int i = 0; i < n; ++i) {
        if (!col[i] && !diag1[x + i] && !diag2[x + n - i]) {
            if (x == n - 1) {
                return 1;
            }

            col[i] = true;
            diag1[x + i] = true;
            diag2[x + n - i] = true;

            res += backtrack(n, x + 1);

            col[i] = false;
            diag1[x + i] = false;
            diag2[x + n - i] = false;
        }
    }

    return res;
}

int main() {
    int n;
    
    cin >> n;
    cout << backtrack(n, 0) << endl;
}
