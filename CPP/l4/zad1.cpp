#include <iostream>

template<typename T>
using fun = T (*)(T);

template<typename T>
void transform(T tab[], int n, fun<T> f) {
    for (int i = 0; i < n; ++i) {
        tab[i] = f(tab[i]);
    }
}

template<typename T>
void print_tab(const T tab[], int n) {
    for (int i = 0; i < n; ++i) {
        std::cout << tab[i];

        if (i < n - 1) {
            std::cout << ' ';
        } else {
            std::cout << std::endl;
        }
    }
}

int add2(int x) {
    return x + 2;
}

float div3(float x) {
    return x / 3;
}

int main() {
    constexpr int N = 5;
    int tab1[N] = {1, 2, 3, 4, 5};
    float tab2[N] = {1, 2, 3, 4, 5};

    transform(tab1, 2, add2);
    transform(tab2, 3, div3);

    print_tab(tab1, N);
    print_tab(tab2, N);

    return 0;
}
