#include <iostream>
#include <iterator>
#include <fstream>
#include <vector>
#include <algorithm>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "Użycie: " << argv[0] << " <k>\n";
        exit(1);
    }

    const std::string arg = argv[1];
    long n;

    try {
        std::size_t pos = 0;
        n = std::stol(argv[1], &pos);
        if (pos != arg.length() || n <= 0) throw std::runtime_error(nullptr);
    } catch (const std::exception &e) {
        std::cerr << "Wartość k, podano: " << arg << ", musi być liczbą > 0\n";
        exit(2);
    }

    std::ofstream f("phi.txt");

    if (!f.is_open()) {
        std::cerr << "Błąd otwarcia phi.txt\n";
        exit(3);
    }

    std::vector<int> phi(n + 1);

    for (int i = 0; i <= n; i++) phi[i] = i;

    for (int i = 2; i <= n; i++) {
        if (phi[i] == i) {
            for (int j = i; j <= n; j += i) phi[j] -= phi[j] / i;
        }
    }

    std::ostream_iterator<int> i_iterator(f, "; ");
    std::copy(phi.begin() + 1, phi.end(), i_iterator);

    f.close();

    std::cout << "Zapisano do phi.txt\n";

    return 0;
}
