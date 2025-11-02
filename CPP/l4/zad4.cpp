#include <functional>
#include <iostream>

int main() {
    const std::function<int(const int, const int)> newton =
        [&newton] (const int n, const int k) {
            if (k == 0 || k == n) return 1;
            if (k > n) return 0;
            return newton(n - 1, k - 1) + newton(n - 1, k);
        };

    std::vector<std::pair<int, int>> vec{{10, 2}, {3, 3}, {15, 4}, {10, -1}};

    for (const auto& [n, k]: vec) {
        std::cout << newton(n, k) << std::endl;
    }

    return 0;
}
