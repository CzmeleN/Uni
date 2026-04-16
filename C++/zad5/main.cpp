#include "kolory.hpp"
#include <iostream>

int main() {
    try {
        kolor k1(100, 150, 200);
        kolor k2(50, 50, 50);
        std::cout << "k1: " << k1 << "\nk2: " << k2 << std::endl;
        std::cout << "diffuse: " << kolor::diffuse(k1, k2) << std::endl;

        k1.brighten(50);
        std::cout << "k1 brightened: " << k1 << std::endl;

        kolor k__err(300, 0, 0);
    } catch (const std::exception& e) {
        std::cout << "złapano: " << e.what() << std::endl;
    }
    std::cout << std::endl;

    try {
        kolortn ktn(255, 0, 0, 128, "czerwony");
        std::cout << ktn << std::endl;
        
        kolortn ktn_err(0, 0, 0, 255, "Czarny");
    } catch (const std::exception& e) {
        std::cout << "złapano: " << e.what() << std::endl;
    }
    std::cout << std::endl;

    try {
        piksel p1(10, 20);
        piksel p2(40, 60);
        std::cout << p1 << ", dist_d: " << p1.dist_d() << std::endl;

        std::cout << "|p1-p2| (ref): " << piksel::dist(p1, p2) << std::endl;
        std::cout << "|p1-p2| (ptr): " << piksel::dist(&p1, &p2) << std::endl;

        piksel p_err(-5, 100);
    } catch (const std::exception& e) {
        std::cout << "złapano: " << e.what() << std::endl;
    }
    std::cout << std::endl;

    try {
        pikselkolorowy pk1(100, 100, 255, 255, 0);
        pikselkolorowy pk2(200, 100, 0, 255, 255);

        std::cout << "pk1: " << pk1 << std::endl;
        pk1.move(50, 50);
        std::cout << "moved: " << pk1 << std::endl;

        pk1.brighten();

        double dist = piksel::dist(pk1, pk2);
        std::cout << "|pk1-pk2| (upcasting: " << dist << std::endl;

        pk1.move(2000, 0);
    } catch (const std::exception& e) {
        std::cout << "złapano: " << e.what() << std::endl;
    }

    return 0;
}
