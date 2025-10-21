#include <iostream>
#include <vector>
#include <set>
#include <iomanip>

void printMixed(int l, int m, bool isNegative) {
    int czesc_calkowita = l / m;
    int reszta_l = l % m;

    std::cout << (isNegative ? "-" : " ");
    
    if (czesc_calkowita > 0) {
        std::cout << std::setw(2) << czesc_calkowita << " ";
    } else {
        std::cout << "   ";
    }

    if (reszta_l > 0) {
        std::cout << std::setw(2) << reszta_l << "/" << std::setw(2) << m;
    } else {
        std::cout << "     ";
    }
    std::cout << "\n";
}

int main() {
    std::set<double> unikalne_wartosci_double;
    std::vector<double> mnozniki_double = {0.5, 1.0, 2.0};

    int mnozniki_licznik[] = {1, 1, 2};
    int mnozniki_mianownik[] = {2, 1, 1};
    std::string mnozniki_nazwa[] = {"2^(-1)", "2^(0)", "2^(1)"};
    
    std::cout << std::fixed << std::setprecision(6);
    std::cout << "--- Wartosci dziesietne jako liczby mieszane (pogrupowane) ---\n";

    for (int i = 0; i < 3; ++i) {
        std::cout << "\nGrupa " << mnozniki_nazwa[i] 
                  << "\n";
        
        for (int e_bits = 0; e_bits <= 15; ++e_bits) {
            int k = 16 + e_bits; // 5 bitów mantysy (16 do 31)
            
            double mantysa_d = static_cast<double>(k) / 32.0;
            double wartosc_d = mantysa_d * mnozniki_double[i];
            unikalne_wartosci_double.insert(wartosc_d);
            unikalne_wartosci_double.insert(-wartosc_d);

            int mantysa_l = k;
            int mantysa_m = 32;

            int final_l = mantysa_l * mnozniki_licznik[i];
            int final_m = mantysa_m * mnozniki_mianownik[i];
            
            printMixed(final_l, final_m, true);
            printMixed(final_l, final_m, false);
        }
    }

    std::cout << "Znaleziono " << unikalne_wartosci_double.size() << " unikalnych wartosci (jako double):\n";

    double A = *unikalne_wartosci_double.begin();
    double B = *unikalne_wartosci_double.rbegin();

    std::cout << "Najmniejszy przedzial [A, B] zawierajacy liczby:\n";
    std::cout << "A = " << A << " (czyli -1 15/16)\n";
    std::cout << "B = " << B << " (czyli  1 15/16)\n";
    std::cout << "Przedzial: [" << A << ", " << B << "]\n";

    return 0;
}
