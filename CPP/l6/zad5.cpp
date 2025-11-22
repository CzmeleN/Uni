#include <iostream>
#include <algorithm>
#include <vector>

std::vector<std::string> permutations(std::string s) {
    std::vector<std::string> ret;
    std::sort(s.begin(), s.end());

    do {
        ret.push_back(s);
    } while (std::next_permutation(s.begin(), s.end()));

    return ret;
}

int main() {
    std::string word = "Word";

    for (const auto& s : permutations(word)) {
        std::cout << s << '\n';
    }

    return 0;
}
