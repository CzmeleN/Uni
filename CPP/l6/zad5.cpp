#include <iostream>
#include <algorithm>
#include <vector>

std::vector<std::string> main(std::string s) {
    std::vector<std::string> ret;
    std::string cs = s;

    do {
        ret.push_back(cs);
    } while (std::next_permutation(cs));
}
