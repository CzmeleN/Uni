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

    for (int k = 0; k < 3; ++k) {
        std::string fn = fns[k];
        std::ofstream f(fn);

        if (!f.is_open()) {
            std::cerr << "Błąd otwarcia " << fn << '\n';
            exit(1);
        }

        for (int i = 0; i < N; ++i) {
            switch (k) {
                case 0:
                    f << uni(gen) << '\n';
                    break;
                case 1:
                    f << bin(gen) << '\n';
                    break;
                case 2:
                    f << norm(gen) << '\n';
                    break;
            }
        }

        f.close();
        std::cout << "Zapisano do: " << fn << '\n';
    }

    return 0;
}
