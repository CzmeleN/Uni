#include <iostream>
#include <regex>
#include <fstream>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cout << "Użycie: " << argv[0] << " <plik html>\n";
        exit(1);
    }

    std::ifstream f(argv[1]);

    if (!f.is_open()) {
        std::cerr << "Błąd otwarcia " << argv[1] << '\n';
        exit(1);
    }

    std::stringstream ss;
    ss << f.rdbuf();

    f.close();

    std::string s = ss.str();

    std::regex reg(R"x(<a\s[^>]*?href="([^"]*)">)x");

    auto beg = std::sregex_iterator(s.begin(), s.end(), reg);

    while (beg != std::sregex_iterator()) {
        std::smatch match = *beg;
        std::cout << match[1].str() << '\n';
        beg++;
    }

    return 0;
}
