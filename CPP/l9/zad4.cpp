#include <iostream>
#include <filesystem>
#include <algorithm>
#include <vector>

constexpr std::string_view ANSI_WHITE = "\033[37m";
constexpr std::string_view ANSI_YELLOW = "\033[33m";

namespace fs = std::filesystem;

int main() {
    std::string s;

    while (std::getline(std::cin, s)) {
        if (s.empty()) continue;

        fs::path p(s);

        if (!fs::exists(p) || !fs::is_directory(p)) {
            std::cerr << "Katalong " << p.string() << " nie istnieje bądź nie jest katalogiem\n";
            continue;
        }

        std::vector<fs::directory_entry> entries;

        try {
            for (const auto &e : fs::directory_iterator(p)) {
                entries.push_back(e);
            }
        } catch (const fs::filesystem_error &e) {
            std::cerr << "Błąd katalogu: " << e.what() << '\n';
            continue;
        }

        std::sort(entries.begin(), entries.end(), [](const fs::directory_entry &a, const fs::directory_entry &b) {
            if (a.is_directory() != b.is_directory()) return a.is_directory() > b.is_directory();

            return a.path().filename() < b.path().filename();
        });

        std::cout << "\nZawartość katalogu " << p.string() << ":\n";

        for (const auto &e : entries) {
            if (e.is_directory()) std::cout << ANSI_YELLOW;

            std::cout << e.path().filename().string() << ANSI_WHITE << '\n';
        }
        
        std::cout << '\n';
    }

    return 0;
}
