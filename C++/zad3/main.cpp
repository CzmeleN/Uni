#include <iostream>
#include <stdexcept>
#include "zmienna.hpp"

int main() {
    zmienna z1("y", 10.0);
    std::cout << "z1 - y: " << z1.get() << std::endl;

    zmienna z2;
    std::cout << "z2 - x: " << z2.get() << std::endl;

    zmienna z3(z1);
    std::cout << "z3 - kopia z1: " << z3.get() << std::endl;

    zmienna z4(std::move(z3));
    std::cout << "z4 - move z3: " << z4.get() << std::endl;

    zmienna z("hist", 1.0);
    z.set(2.0);
    z.set(3.0);
    z.set(4.0);
    z.set(5.0);

    std::cout << "historia z, aktualnie: " << z.get() << std::endl;

    for (int i = 0; i < 3; ++i) {
        z.restore();
        std::cout << "restore z: " << z.get() << std::endl;
    }

    z2 = z1;
    std::cout << "z2 = z1, z2: " << z2.get() << std::endl;

    z2.restore();
    std::cout << "restore z2: " << z2.get() << std::endl;

    z1.neg();
    std::cout << "z1 neg: " << z1.get() << std::endl;

    z1.neg();
    std::cout << "z1 inv: " << z1.get() << std::endl;

    zmienna z0("zero", 0.0);
    try {
        z0.inv();
    } catch (const std::domain_error &e) {
        std::cout << "złapano: " << e.what() << std::endl;
    }
}
