#include <iostream>
#include <ratio>

using namespace std;

template<intmax_t N>
class Harmonic {
public:
    using type = ratio_add<typename Harmonic<N - 1>::type, ratio<1, N>>;
};

template<>
class Harmonic<1> {
public:
    using type = ratio<1, 1>;
};

using h1 = Harmonic<1>::type;
using h2 = Harmonic<2>::type;
using h46 = Harmonic<46>::type;
// using h47 = Harmonic<47>::type; // tu overflow

int main() {
    cout << "h1: " << h1::num << '/' << h1::den
        << "\nh2: " << h2::num << '/' << h2::den
        << "\nh46 (max): " << h46::num << '/' << h46::den << endl;

    return 0;
}
