#include <bits/stdc++.h>
#include <cstdint>

using namespace std;

typedef int_fast32_t fint;

constexpr int N = 100000;

fint tab[N], buff[N];

void merge(int l, int r, int c) {
    int fs = l, ss = c + 1, tab_id = l;

    for (int i = l; i <= r; ++i) {
        buff[i] = tab[i];
    }

    while (fs != c + 1 && ss != r + 1) {
        if (buff[fs] < buff[ss]) {
            tab[tab_id] = buff[fs++];
        } else {
            tab[tab_id] = buff[ss++];
        }

        ++tab_id;
    }

    while (fs != c + 1) {
        tab[tab_id++] = buff[fs++];
    }

    while (ss != r + 1) {
        tab[tab_id++] = buff[ss++];
    }
}

void merge_sort(int l, int r) {
    if (l == r) return;

    if (l + 1 == r) {
        if (tab[l] > tab[r]) {
            swap(tab[l], tab[r]);
        }
    } else {
        int c = (l + r) / 2;

        merge_sort(l, c);
        merge_sort(c + 1, r);
        merge(l, r, c);
    }
}


int main() {
    int n;
    
    cin >> n;

    for (int i = 0; i < n; ++i) {
        cin >> tab[i];
    }

    merge_sort(0, n - 1);

    for (int i = 0; i < n; ++i) {
        cout << tab[i] << ' ';
    }

    cout << endl;

    return 0;
} 
