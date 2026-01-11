#include <iostream>
#include <regex>

int main() {
    std::string s;
    std::regex reg(R"([A-Z][a-z]*((\s+|-)[A-Z][a-z]*)*)");

    while (std::getline(std::cin, s)) {
        if (std::regex_match(s, reg)) {
            std::cout << "dobrze\n";
        } else {
            std::cout << "źle\n";
        }
    }

    return 0;
}
