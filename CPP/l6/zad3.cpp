#include <iostream>
#include <vector>
#include <unordered_map>

using pii = std::pair<int, int>;

std::vector<pii> highest_freq(std::vector<int> nrs) {
    std::unordered_map<int, int> freqs{};

    for (const auto& x : nrs) freqs[x]++;

    std::vector<pii> res;
    int curr_max = 0;

    for (const auto& [k, v] : freqs) {
        if (v < curr_max) continue;

        if (v > curr_max) {
            res.clear();
            curr_max = v;
        }

        res.emplace_back(k, v);
    }

    return res;
}

int main() {
    std::vector<int> nrs = {1, 1, 3, 5, 8, 9, 5, 8, 8, 5};

    for (const auto& p : highest_freq(nrs)) {
        std::cout << p.first << ": " << p.second << '\n';
    }

    return 0;
}
