#include <bits/stdc++.h>

using namespace std;
using ull = unsigned long long;

constexpr int M = 1'000'001;

struct item {
    ull val;
    int row;
    int col;
};

item heap[M];
int m, k;

void heapify() {
    int i = 1, curr, l, r;

    while (true) {
        curr = i;
        l = 2 * i;
        r = 2 * i + 1;

        if (l <= m && heap[l].val > heap[curr].val) {
            curr = l;
        }

        if (r <= m && heap[r].val > heap[curr].val) {
            curr = r;
        }

        if (curr == i) {
            break;
        }

        swap(heap[i], heap[curr]);
        i = curr;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ull last = 0;
    int curr;

    cin >> m >> k;

    curr = m;

    for (int i = 1; i <= m; ++i) {
        heap[i] = {(ull)curr * curr, curr, curr};
        curr--;
    }

    while (k--) {
        while (heap[1].val == last) {
            if (heap[1].col > 0) {
                heap[1].val -= heap[1].row;
                heap[1].col--;
            } else {
                heap[1].val = 0;
            }

            heapify();
        }

        cout << heap[1].val << '\n';

        last = heap[1].val;
    }
    
    return 0;
}
