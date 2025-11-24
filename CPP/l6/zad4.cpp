#include <iostream>
#include <fstream>
#include <iterator>

constexpr int LETTERS = 26;

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "Użycie: " << argv[0] << " <plik>" << '\n';
        exit(1);
    }

    std::ifstream f{argv[1]};

    if (!f.is_open()) {
        std::cerr << "Błąd otwarcia " << argv[1] << '\n';
        exit(2);
    }

    std::istream_iterator<char> it(f);
    constexpr std::istream_iterator<char> end;

    int freqs[LETTERS]{};
    int total = 0;

    std::for_each(it, end, [&freqs, &total](char c) {
        if (isalpha(c)) {
            freqs[tolower(c) - 'a']++; // lepiej std::tolower z locale
            total++;
        }
    });

    f.close();

    if (total == 0) {
        std::cerr << "Plik nie zawierał liter" << '\n';
        exit(3);
    }

    // for (int i = 0; i < LETTERS; ++i) {
    //     std::cout << (char)(i + 'a') << ": " << freqs[i] / (double)total << '\n';
    // }

    for (int i = 0; i < LETTERS; ++i) {
        // lepiej static_cast
        std::cout << (char)(i + 'a') << ": ";
        for (double j = freqs[i] / (double)total; j > 0; j -= 0.05) {
            std::cout << "#";
        }
        std::cout << '\n';
    }

    return 0;
}
