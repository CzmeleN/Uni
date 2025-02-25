#include <bits/stdc++.h>

typedef long long int ll;

using namespace std;

constexpr int N = 100000;

ll bin_search(ll tab[], ll n, ll x) {
    int start = 0;
    int end = n - 1;
    int id;

    while (start <= end) {
        id = (start + end) / 2;

        if (tab[id] < x) {
            start = id + 1;
        } else if (tab[id] > x) {
            end = id - 1;
        } else {
            return id + 1;
        }
    }

    return -1;
}

int main() {
    ll tab[N];
    int n, m, x;

    cin >> n;

    for (int i = 0; i < n; ++i) {
        cin >> x;
        tab[i] = x;
    }

    cin >> m;

    while (m--) {
        cin >> x;
        cout << bin_search(tab, n, x) << endl;
    }
}
