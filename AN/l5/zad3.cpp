#include <iostream>
#include <cmath>
#include <iomanip>

constexpr int maxIter = 10000000;
constexpr double tol = 1e-14;

double w(double x) {
    return pow(x, 5) - x + 1;
}

double dw(double x) {
    return 5 * pow(x, 4) - 1;
}

void bisekcja(double a, double b, double tol, int maxIter) {
    double fa = w(a);
    double c;

    std::cout << "bisekcja: \t";

    for (int i = 1; i <= maxIter; ++i) {
        c = (a + b) / 2.0;
        double fc = w(c);

        if (fabs(fc) < tol) {
            std::cout << c << " (" << i << " iter)\n";
            return;
        }

        if (fa * fc < 0) {
            b = c;
        } else {
            a = c;
            fa = fc;
        }
    }
    std::cout << "nie osiagnieto zbieznosci\n";
}

void newton(double x0, double tol, int maxIter) {
    double x = x0;

    for (int i = 1; i <= maxIter; ++i) {
        double fx = w(x);
        double dfx = dw(x);

        if (fabs(fx) < tol) {
            std::cout << "newton: \t" << x << " (" << i << " iter)\n";
            return;
        }

        x = x - fx / dfx;
    }
    std::cout << "newton: \tnie osiagnieto zbieznosci\n";
}

void sieczne(double x0, double x1, double tol, int maxIter) {
    double x_prev = x0;
    double x_curr = x1;
    double f_prev = w(x_prev);
    double f_curr = w(x_curr);

    for (int i = 1; i <= maxIter; ++i) {
        if (fabs(f_curr) < tol) {
            std::cout << "sieczne: \t" << x_curr << " (" << i << " iter)\n";
            return;
        }

        double x_next = x_curr - f_curr * (x_curr - x_prev) / (f_curr - f_prev);

        x_prev = x_curr;
        f_prev = f_curr;
        x_curr = x_next;
        f_curr = w(x_curr);
    }
    std::cout << "sieczne: \tnie osiagnieto zbieznosci\n";
}

void regula_falsi(double a, double b, double tol, int maxIter) {
    double fa = w(a);
    double fb = w(b);
    double x_new;

    for (long long i = 1; i <= maxIter; ++i) {
        x_new = a - fa * (b - a) / (fb - fa);
        double fx_new = w(x_new);

        if (fabs(fx_new) < tol) {
            std::cout << "regula falsi: \t" << x_new << " (" << i << " iter)\n";
            return;
        }

        if (fa * fx_new < 0) {
            b = x_new;
            fb = fx_new;
        } else {
            a = x_new;
            fa = fx_new;
        }
    }
    std::cout << "regula falsi: \tnie osiagnieto zbieznosci";
}

int main() {
    double a = -1.6;
    double b = -0.5;
    double x_n = -1.2;
    double x0_s = -2.0;
    double x1_s = -1.0;

    std::cout << std::fixed << std::setprecision(16);
    std::cout << "dokładnie: -1.1673039782614187...\n\n";

    bisekcja(a, b, tol, maxIter);
    regula_falsi(a, b, tol, maxIter);
    sieczne(x0_s, x1_s, tol, maxIter);
    newton(x_n, tol, maxIter);

    return 0;
}
