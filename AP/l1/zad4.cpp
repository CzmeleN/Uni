#include <bits/stdc++.h>

using namespace std;

constexpr int N = 1'000'001;

int phi[N];

void count_phis() {
    for (int i = 1; i < N; ++i) {
        phi[i] = i;
    }

    for (int i = 2; i < N; ++i) {
        if (phi[i] == i) {
            for (int j = i; j < N; j += i) {
                phi[j] -= phi[j] / i;
            }
        }
    }
}

int main() {
    int x, n;

    count_phis();

    cin >> n;

    while (n--) {
        cin >> x;
        cout << phi[x] << endl;
    }
}
