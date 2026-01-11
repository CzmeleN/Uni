#include <iostream>
#include <regex>

// rozpowznawane godzine - 0-23, 0-59) oddzielone :, oba dwie cyfry, opconalnie :0-59 sekundy

int main() {
    std::string s;
    std::regex reg(R"((([0-1]\d)|(2[0-3])):[0-5]\d(:[0-5]\d)?)");

    while (std::cin >> s) {
        if (std::regex_match(s, reg)) {
            std::cout << "dobrze\n";
        } else {
            std::cout << "źle\n";
        }
    }

    return 0;
}
