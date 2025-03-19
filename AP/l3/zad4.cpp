#include <bits/stdc++.h>

using namespace std;

constexpr int N = 100'000;

struct Query {
    int l, r, id;
};

Query queries[N];
int n, q, block_s = 1, curr_res = 0;
int arr[N];
int freq[N];
int res[N];

bool cmp(Query a, Query b) {
    int block_a = a.l / block_s;
    int block_b = b.l / block_s;

    if (block_a != block_b) {
        return block_a < block_b;
    }

    return a.r < b.r;
}

void add(int id) {
    int x = arr[id];

    if (x > n) return;
    
    if (freq[x] == x) {
        curr_res--;
    }

    freq[x]++;

    if (freq[x] == x) {
        curr_res++;
    }
}

void remove(int id) {
    int x = arr[id];

    if (x > n) return;
    
    if (freq[x] == x) {
        curr_res--;
    }

    freq[x]--;

    if (freq[x] == x) {
        curr_res++;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int p, k, curr_l = 0, curr_r = -1, l, r;

    cin >> n >> q;

    for (int i = 0; i < n; ++i) {
        cin >> arr[i];
    }

    for (int i = 0; i < q; ++i) {
        cin >> p >> k;
        p--; k--;

        queries[i] = {p, k, i};
    }

    while (block_s * block_s < n) block_s++;

    sort(queries, queries + q, cmp);

    for (int i = 0; i < q; i++){
        l = queries[i].l;
        r = queries[i].r;

        while (curr_r < r) {
            curr_r++;
            add(curr_r);
        }

        while (curr_r > r) {
            remove(curr_r);
            curr_r--;
        }

        while (curr_l < l) {
            remove(curr_l);
            curr_l++;
        }

        while (curr_l > l) {
            curr_l--;
            add(curr_l);
        }

        res[queries[i].id] = curr_res;
    }

    for (int i = 0; i < q; ++i) {
        cout << res[i] << '\n';
    }

    return 0;
}
