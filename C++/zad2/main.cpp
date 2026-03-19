#include <iostream>
#include <type_traits>
#include <iomanip>

#include "basic.hpp"
#include "shapes.hpp"

template<typename... Args>
void are_pod() {
    ([&]{
        std::cout << typeid(Args).name();
        if constexpr (std::is_standard_layout_v<Args> && std::is_trivial_v<Args>) std::cout << " jest POD" << std::endl;
        else std::cout << " nie jest POD" << std::endl;
    }(), ...);
}

void print_p(const std::string& label, punkt p) {
    std::cout << label << '(' << p.x << ", " << p.y << ')' << std::endl;
}

int main() {
    are_pod<punkt, prosta, wektor>();

    try {
        std::cout << std::fixed << std::setprecision(2);

        std::cout << "\n> punkt p" << std::endl;
        punkt p{1.0, 1.0};
        print_p("poczatkowy: ", p);

        p.move({2.0, -1.0});
        print_p("po przesunieciu [2, -1]: ", p);

        p.rotate({0.0, 0.0}, 90.0);
        print_p("po obrocie 90 wokol 0: ", p);

        p.mirror(punkt{0.0, 0.0});
        print_p("po symetrii wzgledem 0: ", p);
        std::cout << std::endl;

        std::cout << "> odcinek" << std::endl;
        odcinek s1({0, 0}, {4, 0});
        odcinek s2({0, 2}, {4, 2});
        odcinek s3({0, 0}, {0, 4});

        std::cout << "dł s1: " << s1.len() << std::endl;
        std::cout << "(2,0) leży na s1? " << (s1.is_on({2, 0}) ? 'T' : 'N') << std::endl;
        std::cout << "s1 || s2? " << (are_parallel(s1, s2) ? 'T' : 'N') << std::endl;
        std::cout << "s1 prostopadły do s3? " << (are_perpendicular(s1, s3) ? 'T' : 'N') << std::endl;
        std::cout << std::endl;

        std::cout << "> trojkat" << std::endl;
        trojkat t1({0, 0}, {4, 0}, {0, 3});
        std::cout << "pole t1: " << t1.area() << " (6.00)" << std::endl;
        std::cout << "Obwod t1: " << t1.perimeter() << " (12.00)" << std::endl;
        std::cout << "(1,1) wewnatrz t1? " << (t1.is_inside({1, 1}) ? 'T' : 'N') << std::endl;

        trojkat t2({10, 10}, {14, 10}, {10, 13});
        std::cout << "t1, t2 rozłączne? " << (are_disjoint(t1, t2) ? 'T' : 'N') << std::endl;
        
        trojkat t3({0.1, 0.1}, {0.2, 0.1}, {0.1, 0.2});
        std::cout << "t3 wewnątrz t1? " << (is_contained(t1, t3) ? 'T' : 'N') << std::endl;
        std::cout << std::endl;

        std::cout << "> wyjątki" << std::endl;

        try { odcinek s({1, 1}, {1, 1}); }
        catch (const std::invalid_argument& e) { std::cout << "złapany: " << e.what() << std::endl; }

        try { trojkat t({0, 0}, {1, 1}, {2, 2}); }
        catch (const std::invalid_argument& e) { std::cout << "złapany: " << e.what() << std::endl; }

        try { p.mirror({0, 0, 5}); }
        catch (const std::invalid_argument& e) { std::cout << "złapany: " << e.what() << std::endl; }

    } catch (const std::exception& e) {
        std::cerr << "nieoczekiwany bł: " << e.what() << std::endl;
    }
}
