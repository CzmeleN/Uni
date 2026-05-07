#include "wymierna.hpp"
#include <iostream>
#include <sstream>
#include <cassert>
#include <limits>

using namespace obliczenia;

void test_basic() {
    wymierna w1;
    assert(w1.get_nom() == 0 && w1.get_den() == 1);

    wymierna w2(5);
    assert(w2.get_nom() == 5 && w2.get_den() == 1);

    wymierna w3(2, 4);
    assert(w3.get_nom() == 1 && w3.get_den() == 2);

    wymierna w4(3, -9);
    assert(w4.get_nom() == -1 && w4.get_den() == 3);

    wymierna w5 = w4;
    assert(w5.get_nom() == -1 && w5.get_den() == 3);

    wymierna w6;
    w6 = w3;
    assert(w6.get_nom() == 1 && w6.get_den() == 2);

    std::cout << "basic OK" << std::endl;
}

void test_maths() {
    wymierna a(1, 2);
    wymierna b(1, 3);

    wymierna res = a + b;
    assert(res.get_nom() == 5 && res.get_den() == 6);

    res = a - b;
    assert(res.get_nom() == 1 && res.get_den() == 6);

    res = a * b;
    assert(res.get_nom() == 1 && res.get_den() == 6);

    res = a / b;
    assert(res.get_nom() == 3 && res.get_den() == 2);

    wymierna c(1, 4);
    c += wymierna(3, 4);
    assert(c.get_nom() == 1 && c.get_den() == 1);

    wymierna u(-1, 2);
    wymierna n_u = -u;
    assert(n_u.get_nom() == 1 && n_u.get_den() == 2);

    wymierna odw = !u;
    assert(odw.get_nom() == -2 && odw.get_den() == 1);

    std::cout << "maths OK" << std::endl;
}

void test_casts() {
    wymierna w(5, 2);
    double d = static_cast<double>(w);
    assert(d == 2.5);

    int i1 = static_cast<int>(wymierna(2, 3));
    assert(i1 == 1);

    int i2 = static_cast<int>(wymierna(1, 3));
    assert(i2 == 0);

    int i3 = static_cast<int>(wymierna(-5, 2));
    assert(i3 == -3);

    std::cout << "casts OK" << std::endl;
}

void test_streams() {
    wymierna w1(2359348, 99900);
    std::ostringstream o1;
    o1 << w1;
    assert(o1.str() == "23.61(709)");

    wymierna w2(-1, 3);
    std::ostringstream o2;
    o2 << w2;
    assert(o2.str() == "-0.(3)");

    wymierna w3(1, 2);
    std::ostringstream o3;
    o3 << w3;
    assert(o3.str() == "0.5");

    std::istringstream in("4/-8");
    wymierna w4;
    in >> w4;
    assert(w4.get_nom() == -1 && w4.get_den() == 2);

    std::cout << "streams OK" << std::endl;
}

void test_excepts() {
    bool caught = false;

    try {
        wymierna w(1, 0);
    } catch (const dzielenie_przez_0& e) {
        caught = true;
    }
    assert(caught);

    caught = false;
    try {
        wymierna w(0, 1);
        !w;
    } catch (const dzielenie_przez_0& e) {
        caught = true;
    }
    assert(caught);

    caught = false;
    try {
        wymierna w1(std::numeric_limits<int>::max(), 1);
        wymierna w2(std::numeric_limits<int>::max(), 1);
        wymierna res = w1 + w2;
        !res;
    } catch (const przekroczenie_zakresu& e) {
        caught = true;
    }
    assert(caught);

    std::cout << "excepts OK" << std::endl;
}

int main() {
    test_basic();
    test_maths();
    test_casts();
    test_streams();
    test_excepts();

    std::cout << "all OK" << std::endl;

    return 0;
}
