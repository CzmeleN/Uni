#include <complex>
#include <iostream>

using cd = std::complex<double>;

constexpr cd em(0.5772156649);
constexpr cd one(1.0);
constexpr int much_iter = 1000;

cd eul_gamma(cd z, int it = 10) {
    cd x = one;

    for (int i = 1; i <= it; ++i) {
        cd n(static_cast<double>(i));
        x *= std::exp(z / n) / (one + z / n);
    }

    return (std::exp(-em * z) / z) * x;
}

cd eul_gamma_inv(cd z, int it = 10) {
    cd x = one;

    for (int i = 1; i <= it; ++i) {
        cd n(static_cast<double>(i));
        x *= (one + z / n) / std::exp(z / n);
    }

    return z * std::exp(em * z) * x;
}

int main() {
    cd c(3.0, 4.0);

    std::cout << "gamma 10 it: " << eul_gamma(c) << "\ninv gamma 10 it: " << eul_gamma_inv(c);
    std::cout << "\niloczyn g * inv: " << eul_gamma(c, much_iter) * eul_gamma_inv(c, much_iter) << '\n';

    return 0;
}
