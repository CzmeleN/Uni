#include "tabbit.hpp"
#include <iostream>

int main() {
    tabbit t(46); // tablica 46-bitowa (zainicjalizowana zerami)
    // tabbit u(45ull); // tablica 64-bitowa (sizeof(uint64_t)*8)
    tabbit u(static_cast<uint64_t>(45)); // tablica 64-bitowa (sizeof(uint64_t)*8)
    tabbit v(t); // tablica 46-bitowa (skopiowana z t)
    tabbit w {1, 0, 1, 1, 0, 0, 0, 1}; // tablica 8-bitowa
    v[0] = 1; // ustawienie bitu 0-go bitu na 1
    t[45] = true; // ustawienie bitu 45-go bitu na 1
    bool b = v[1]; // odczytanie bitu 1-go
    std::cout << b << std::endl;
    u[45] = u[46] = u[63]; // przepisanie bitu
    std::cout << t << std::endl; // wyświetlenie zawartości tablicy bitów
    
    return 0;
}
