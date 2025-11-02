#include <iostream>
#include <vector>
#include <numeric>
#include <list>
#include <set>

void inline print_sep(bool &is_first) {
    if (!is_first) {
        std::cout << ' ';
    } else {
        is_first = false;
    }
}

template<typename T>
class PrintBetween {
private:
    T a;
    T b;
public:
    PrintBetween(T a_val, T b_val) : a(a_val), b(b_val) {};

    template<typename Ts>
    void operator() (const Ts& xs) const {
        bool is_first = true;

        for (const auto &x : xs) {
            if (x > a && x < b) {
                print_sep(is_first);
                std::cout << x;
            }
        }

        std::cout << std::endl;
    }
};

class PrintEvery {
private:
    size_t k;
    size_t p;
public:
    PrintEvery(size_t k_val, size_t p_val) : k(k_val), p(p_val) {};

    template<typename size_ts>
    void operator() (const size_ts& xs) const {
        bool is_first = true;
        size_t i = 0, j = k;

        for (const auto& x : xs) {
            if (i++ >= p) {
                if (++j >= k) {
                    print_sep(is_first);
                    std::cout << x;
                    j = 0;
                }
            }
        }

        std::cout << std::endl;
    }
};

class MinMax {
public:
    template<typename T>
    const auto operator() (const T& xs) const {
        return std::make_pair(*std::min_element(xs.begin(), xs.end()), *std::max_element(xs.begin(), xs.end()));
    }
};

template<typename T>
void print_pair(const T& p) {
    std::cout << p.first << ' ' << p.second << std::endl;
}

class Sum {
public:
    template<typename T>
    const auto operator() (const T& xs) const {
        return std::accumulate(xs.begin(), xs.end(), typename T::value_type{});
    }
};

int main() {
    std::vector<double> vd{1.0, 2.0, -3.0, 5.5, 9.0, -4.0};
    std::list<int> li{1, 3, 2, 4, -4, 10, -7, 12};
    std::set<std::string> ss{"Jan", "Józef", "Kuba", "Dawid"};

    PrintBetween(1.0, 6.0)(vd);
    PrintBetween(-5, 10)(li);
    PrintBetween("E", "Jz")(ss);

    std::cout << std::endl;

    PrintEvery(2, 1)(vd);
    PrintEvery(2, 2)(li);
    PrintEvery(3, 0)(ss);

    std::cout << std::endl;

    const auto p1 = MinMax()(vd);
    const auto p2 = MinMax()(li);
    const auto p3 = MinMax()(ss);
    print_pair(p1);
    print_pair(p2);
    print_pair(p3);

    std::cout << std::endl;

    const auto s1 = Sum()(vd);
    const auto s2 = Sum()(li);
    const auto s3 = Sum()(ss);
    std::cout << s1 << '\n' << s2 << '\n' << s3 << std::endl;

    return 0;
}
