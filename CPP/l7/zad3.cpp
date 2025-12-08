#include <random>
#include <fstream>
#include <iostream>
#include <stdexcept>

void write(long len, std::ofstream &f, std::mt19937 &gen) {
    static std::discrete_distribution<> freq_dist({
        8.17, 1.49, 2.78, 4.25, 12.70, 2.23, 2.02, 6.09, 6.97, 0.15,
        0.77, 4.03, 2.41, 6.75, 7.51, 1.93, 0.10, 5.99, 6.33, 9.06,
        2.76, 0.98, 2.36, 0.15, 1.97, 0.07
    });
    static std::binomial_distribution<> len_dist(11, 0.5);
    static const std::string alphabet = "abcdefghijklmnopqrstuvwxyz";

    int word = len_dist(gen) + 1;

    while (len--) {
        if (word == 0) {
            f << ' ';
            word = len_dist(gen) + 1;
        } else {
            f << alphabet[freq_dist(gen)];
            word--;
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        std::cerr << "Użycie: " << argv[0] << " <dł. tekstu> <pliik wyjście (program doda .txt)>\n";
        exit(1);
    }

    const std::string arg = argv[1];
    long len;

    try {
        std::size_t pos = 0;
        len = std::stol(argv[1], &pos);
        if (pos != arg.length() || len <= 0) throw std::runtime_error(nullptr);
    } catch (const std::exception &e) {
        std::cerr << "Dł. tekstu, podano: " << arg << ", musi być liczbą > 0\n";
        exit(2);
    }

    std::string fn = std::string(argv[2]) + ".txt";
    std::ofstream f{fn};

    if (!f.is_open()) {
        std::cerr << "Błąd otwarcia " << fn << '\n';
        exit(3);
    }

    std::random_device rd;
    std::mt19937 gen(rd());

    write(len, f, gen);

    f.close();

    std::cout << "Pomyślnie zapisano do: " << fn << '\n';

    return 0;
}
