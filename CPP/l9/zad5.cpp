#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

int main() {
    std::string s;

    while (std::getline(std::cin, s)) {
        fs::path p(s);

        if (!fs::exists(p) || !fs::is_directory(p)) {
            std::cerr << "Katalong " << p.string() << " nie istnieje bądź nie jest katalogiem\n";
            continue;
        }

        size_t sum = 0;
        size_t f_count = 0;

        try {
            for (const auto &e : fs::recursive_directory_iterator(p, fs::directory_options::skip_permission_denied)) {
                try {
                    if (fs::is_regular_file(e)) {
                        sum += fs::file_size(e);
                        f_count ++;
                    }
                } catch (const fs::filesystem_error& err) {
                    std::cerr << "Błąd pliku: " << e.path().filename() << "]\n";
                }
            }

            std::cout << fs::canonical(p).string() << ":\n";
            std::cout << "# plików:    " << f_count << '\n';
            std::cout << "Rozmiar: " << sum << "B\n\n";
        } catch (const fs::filesystem_error& err) {
            std::cerr << "Błąd katalogu: " << err.what() << '\n';
        }
    }

    return 0;
}
