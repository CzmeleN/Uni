#include <exception>
#include <string>
#include <iostream>
#include <stdexcept>
#include <vector>

using pis = std::pair<int, std::string>;

std::string to_roman(int x) {
    static const std::vector<pis> roman = {
        {1000, "M"},
        {900, "CM"}, {500, "D"}, {400, "CD"}, {100, "C"},
        {90, "XC"}, {50, "L"}, {40, "XL"}, {10, "X"},
        {9, "IX"}, {5, "V"}, {4, "IV"}, {1, "I"}
    };

    std::string res = "";
    auto it = roman.begin();

    while (x) {
        if (x >= it->first) {
            x -= it->first;
            res += it->second;
        } else {
            it++;
        }
    }

    return res;
}

int main(int argc, char *argv[]) {
    if (argc <= 1) std::clog << "Usage: " << argv[0] << " <number> <number> ...\n";

    for (int i = 1; i < argc; ++i) {
        int x;

        try {
            x = std::stoi(argv[i]);
            if (x < 1 || x > 3999) throw std::invalid_argument(argv[i]);
        } catch (std::exception &e) {
            std::clog << "Invalid argument: " << e.what() << '\n';
            continue;
        }

        std::cout << to_roman(x) << '\n';
    }
    return 0;
}
