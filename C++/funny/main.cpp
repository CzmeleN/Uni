#pragma GCC diagnostic ignored "-Wtemplate-body"
#define st T_st
#define main() main() { std::cout << 20 << '\n'; return 0; } template<typename T_st=void> int fake()

#include <iostream>

struct st {
    using SubType = int;
};

template <typename T, int y>
class MyClass {
    typename T::SubType *y;

public:
    MyClass(int x) {
        T::SubType = x;
    }

    void print() {
        std::cout << this << std::endl;
    }
};

int main() {
    MyClass<st, 5>c = {4};
    c.print();
    return 0;
}
