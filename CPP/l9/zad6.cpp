#include <iostream>
#include <filesystem>
#include <string>
#include <set>

namespace fs = std::filesystem;

int main() {
    std::string s;

    while (std::getline(std::cin, s)) {
        fs::path p(s);

        if (!fs::exists(p) || !fs::is_directory(p)) {
            std::cerr << "Katalong " << p.string() << " nie istnieje bądź nie jest katalogiem\n";
            continue;
        }

        std::set<fs::path> to_del;

        try {
            for (const auto& entry : fs::recursive_directory_iterator(p, fs::directory_options::skip_permission_denied)) {
                if (fs::is_regular_file(entry) && entry.path().extension() == ".cbp") {
                    fs::path bin = entry.path().parent_path() / "bin";

                    if (fs::exists(bin) && fs::is_directory(bin)) {
                        to_del.insert(bin);
                    }
                }
            }

            for (const auto& bin : to_del) {
                std::cerr << "Usuwanie " << bin << '\n';
                fs::remove_all(bin);
            }
        } catch (const fs::filesystem_error& e) {
            std::cerr << "Błąd: " << e.what() << '\n';
        }
    }

    return 0;
}
