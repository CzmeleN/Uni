#include <iostream>
#include <fstream>
#include <random>

constexpr int N = 1000;

int main() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::string fns[3]{ "uniform_real.csv", "binomial.csv", "normal.csv" };
    std::uniform_real_distribution<double> uni(0.0, 1.0);
    std::binomial_distribution<int> bin(10);
    std::normal_distribution<double> norm(5.0, 2.0);
    std::ofstream fs[3];

    for (int i = 0; i < 3; ++i) {
        std::string fn = fns[i];
        fs[i] = std::ofstream(fn);

        if (!fs[i].is_open()) {
            std::cerr << "Błąd otwarcia " << fn << '\n';
            exit(1);
        }
    }

    for (int i = 0; i < N; ++i) {
        fs[0] << uni(gen) << '\n';
        fs[1] << bin(gen) << '\n';
        fs[2] << norm(gen) << '\n';
    }

    for (int i = 0; i < 3; ++i) {
        std::cout << "Zapisano plik: " << fns[i] << '\n';
    }

    return 0;
}
