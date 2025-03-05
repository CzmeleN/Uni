#include <bits/stdc++.h>

using namespace std;

constexpr int N = 1'000'001;

int d_count[N];

void count_ds() {
    for (int i = 1; i < N; ++i) {
        d_count[i] = 1;
    }

    for (int i = 2; i < N; ++i) {
        for (int j = i; j < N; j += i) {
            d_count[j] += 1;
        }
    }
}

int main() {
    int x, n;

    count_ds();

    cin >> n;

    while (n--) {
        cin >> x;
        cout << d_count[x] << endl;
    }
}
