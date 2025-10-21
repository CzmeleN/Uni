#include <iostream>
#include <limits>

int main() {
    float x = 0.5 * std::numeric_limits<float>::max();
    float y = 0.5 * std::numeric_limits<float>::max();

    float d = x * x;
    d -= y * y;

    std::cout << d << std::endl;

    return 0;
}
