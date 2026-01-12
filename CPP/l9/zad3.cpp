#include <exception>
#include <iostream>
#include <chrono>
#include <format>
#include <filesystem>

namespace fs = std::filesystem;

void print_time(const fs::path &p) {
    try {
        auto ftime = fs::last_write_time(p);
        auto sys_time = std::chrono::clock_cast<std::chrono::system_clock>(ftime);

        std::cout << "Data modyfikacji: " << std::format("{:%Y-%m-%d %H:%M:%S}", sys_time) << '\n';
    } catch (const std::exception &e) {
        std::cout << "Data modyfikacji: Błąd:" << e.what() << '\n';
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cerr << "Użycie: " << argv[0] << " <plik1> <plik2> <...>\n";
        exit(1);
    }

    for (int i = 1; i < argc; ++i) {
        fs::path p(argv[i]);

        std::cout << argv[i] << '\n';

        if (fs::exists(p)) {
            try {
                std::cout << "Ścieżk: " << fs::canonical(p);

                if (fs::is_directory(p)) {
                    std::cout << "Katalog\n";
                } else if (fs::is_regular_file(p)) {
                    std::cout << "Plik\n";
                    std::cout << "Rozmiar: " << fs::file_size(p) << "B\n";
                } else if (fs::is_symlink(p)) {
                    std::cout << "Symlink\n";
                } else {
                    std::cout << "Inny\n";
                }

                print_time(p);
            } catch (const fs::filesystem_error &e) {
                std::cerr << "Błąd: " << e.what() << '\n';
            }
        } else {
            std::cout << "Nie ma takiego pliku/katalogu\n";
        }
    }

    return 0;
}
