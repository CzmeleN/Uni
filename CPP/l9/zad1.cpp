#include <iomanip>
#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <cmath>

int main() {
    std::ifstream f("liczby.txt");

    if (!f.is_open()) {
        std::cerr << "Błąd otwarcia liczby.txt\n";
        exit(1);
    }

    std::vector<float> vec((std::istream_iterator<float>(f)), std::istream_iterator<float>());

    float avg = 0;

    for (const float x : vec) {
        avg += x;
    }

    avg /= vec.size();

    float dev = 0;

    for (const float x : vec) {
        dev += (x - avg) * (x - avg);
    }

    dev = sqrt(dev / vec.size());

    std::cout << std::fixed << std::setprecision(3) << "Średnia: " << avg << " odchylenie: " << dev << '\n';

    return 0;
}
