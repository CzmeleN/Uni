#include <bits/stdc++.h>

using namespace std;
using ull = unsigned long long;

constexpr int N = 1'000'000;
constexpr int BITS = 20;

struct Point {
    int x, y, id;
    ull order;
};

Point points[N];

ull hilbert_order(int x, int y) {
    int rx, ry;
    ull order = 0;

    for (int i = BITS - 1; i >= 0; --i) {
        rx = (x >> i) & 1;
        ry = (y >> i) & 1;

        order = (order << 2) | (ull)((rx << 1) | (rx ^ ry));

        if (ry == 0 && rx == 1) {
            x = (1 << BITS) - 1 - x;
            y = (1 << BITS) - 1 - y;
        }

        swap(x, y);
    }

    return order;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;

    cin >> n;

    for (int i = 0; i < n; ++i) {
        cin >> points[i].x >> points[i].y;

        points[i].id = i + 1;
        points[i].order = hilbert_order(points[i].x, points[i].y);
    }

    sort(points, points + n, [](const Point &a, const Point &b) {
        return a.order < b.order;
    });

    for (int i = 0; i < n; ++i) {
        cout << points[i].id << ' ';
    }

    cout << '\n';

    return 0;
}
