#pragma once
#include <iostream>
#include <cstring>

template<typename T>
void arrprint(const T arr[], int siz, std::ostream &out = std::cout) {
    out << '[';

    for (int i = 0; i < siz; ++i) {
        out << arr[i];

        if (i != siz - 1) out << ' ';
    }

    out << ']' << std::endl;
}

template<typename T>
void arrcopy(const T from[], int siz, T to[]) {
    if (from == to || siz <= 0) return;

    if (to > from && to < from + siz)
        for (int i = siz - 1; i >= 0; --i) to[i] = from[i];
    else
        for (int i = 0; i < siz; ++i) to[i] = from[i];
}

template<typename T>
void arrpermut(T arr[], int siz) {
    for (int i = siz - 1; i > 0; --i) {
        int j = std::rand() % (i + 1);

        std::swap(arr[i], arr[j]);
    }
}

template<typename T>
class less {
public:
    bool operator()(const T &a, const T &b) const {
        return a < b;
    }
};

template<>
class less<const char*> {
public:
    bool operator()(const char* const &a, const char* const &b) const {
        return std::strcmp(a, b) < 0;
    }
};

template<typename T>
class greater {
public:
    bool operator()(const T &a, const T &b) const {
        return a > b;
    }
};

template<>
class greater<const char*> {
public:
    bool operator()(const char* const &a, const char* const &b) const {
        return std::strcmp(a, b) > 0;
    }
};

template<typename T, typename Compare = less<T>>
void arrsort_bubble(T arr[], int siz, Compare comp = Compare()) {
    for (int i = 0; i < siz - 1; ++i) {
        for (int j = 0; j < siz - i - 1; ++j) {
            if (comp(arr[j + 1], arr[j])) std::swap(arr[j], arr[j + 1]);
        }
    }
}

template <typename T, typename Compare>
int partition(T arr[], int l, int h, Compare comp) {
    T p = arr[h];
    int i = l - 1;

    for (int j = l; j <= h - 1; j++) {
        if (comp(arr[j], p)) {
            i++;
            std::swap(arr[i], arr[j]);
        }
    }

    std::swap(arr[i + 1], arr[h]);

    return (i + 1);
}

template <typename T, typename Compare>
void quicksort(T arr[], int l, int h, Compare comp) {
    if (l < h) {
        int m = partition(arr, l, h, comp);
        quicksort(arr, l, m - 1, comp);
        quicksort(arr, m + 1, h, comp);
    }
}

template<typename T, typename Compare = less<T>>
void arrsort_quick(T arr[], int siz, Compare comp = Compare()) {
    if (siz > 1) quicksort(arr, 0, siz - 1, comp);
}
