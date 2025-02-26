#include <bits/stdc++.h>

using namespace std;

void shift_down(vector<int> &tab, int n, int i) {
    int largest = i;
    int lc = 2 * i + 1;
    int rc = 2 * i + 2;

    if (lc < n && tab[lc] > tab[largest]) {
        largest = lc;
    }

    if (rc < n && tab[rc] > tab[largest]) {
        largest = rc;
    }

    if (largest != i) {
        swap(tab[i], tab[largest]);
        shift_down(tab, n, largest);
    }
}

void heap_sort(vector<int> &tab, int n) {
    for (int i = n / 2 - 1; i >= 0; --i) {
        shift_down(tab, n, i);
    }

    for (int i = n - 1; i >= 0; --i) {
        swap(tab[0], tab[i]);
        shift_down(tab, i, 0);
    }
}

int main() {
    int n;
    
    cin >> n;

    vector<int> tab(n);

    for (int i = 0; i < n; ++i) {
        cin >> tab[i];
    }

    heap_sort(tab, n);

    for (int i = 0; i < n; ++i) {
        cout << tab[i] << ' ';
    }

    cout << endl;

    return 0;
} 
