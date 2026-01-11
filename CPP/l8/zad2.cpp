#include <iostream>
#include <regex>

// daty dd-mm-yyyy, luty 28 dni

int main() {
    std::string s;
    std::regex reg(R"(((0[1-9]|[12]\d|30)-(0[13-9]|1[0-2])|31-(0[13578]|1[02])|(0[1-9]|1\d|2[0-8])-02)-\d{4})");

    while (std::cin >> s) {
        if (std::regex_match(s, reg)) {
            std::cout << "dobrze\n";
        } else {
            std::cout << "źle\n";
        }
    }

    return 0;
}
