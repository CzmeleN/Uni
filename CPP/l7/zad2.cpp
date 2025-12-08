#include <complex>
#include <iostream>
#include <fstream>

using cd = std::complex<double>;

constexpr cd one(1.0);
constexpr cd zero(0.0);
constexpr int much_iter = 1000;

cd dzeta(cd z, int it = 10) {
    cd x = zero;

    for (int i = 1; i <= it; ++i) {
        x += one / std::pow(cd(static_cast<double>(i)), z);
    }

    return x;
}

cd dzeta_r(cd z, int it = 10) {
    cd x = zero;

    for (int i = 1; i <= it; ++i) {
        x += (i % 2 == 0 ? -one : one) / std::pow(cd(static_cast<double>(i)), z);
    }

    return one / (one - std::pow(cd(2.0), one - z));
}

int main() {
    cd c1(3.0, 4.0);

    for (int i = 100; i <= 1000; i += 100) {
        std::cout << "dzeta od r=3.0, i=4.0, iter=" << i << ": " << dzeta(c1, i) << '\n';
    }

    std::ofstream f("zad2.csv");

    if (!f.is_open()) {
        std::cerr << "Błąd otwarcia zad2.csv\n";
        exit(1);
    }

    f << "y,real,imag\n";

    double r = 0.5;

    for (double i = -30.0; i < 30.01; i += 0.05) {
        cd res = dzeta_r(cd(r, i), much_iter);
        f << i << ',' << res.real() << ',' << res.imag() << '\n';
    }

    f.close();

    std::cout << "mamy csv\n";

    return 0;
}
