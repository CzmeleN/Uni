#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n;
    ll x, y, first_x, first_y, prev_x, prev_y, sum = 0, half;

    cin >> n;
    cin >> first_x >> first_y;

    prev_x = first_x;
    prev_y = first_y;

    while (--n) {
        cin >> x >> y;

        sum += prev_x * y - x * prev_y;

        prev_x = x;
        prev_y = y;
    }

    sum += x * first_y - first_x * y;
    sum = abs(sum);
    half = sum / 2;

    cout << half << '.' << (half * 2 == sum ? '0' : '5') << '\n';

    return 0;
}
