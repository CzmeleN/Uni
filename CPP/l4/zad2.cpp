#include <iostream>
#include <functional>

template<typename T>
using fun = std::function<void(T)>;

template<typename T>
class PoKolei {
private:
    fun<T> f1;
    fun<T> f2;
public:
    PoKolei(fun<T> fun1, fun<T> fun2) : f1(fun1), f2(fun2) {};

    void operator() (const T& x) const {
        f1(x);
        f2(x);
    }
};

template<typename T>
void print_val(const T& x) {
    std::cout << x << std::endl;
}

template<typename T>
void print_dashed(const T& x) {
    std::cout << "--- " << x << " ---" << std::endl;
}

template<typename T>
void print_usd(const T& x) {
    std::cout << '$' << x << std::endl;
}

int main() {
    PoKolei<std::string>(print_val<std::string>, print_dashed<std::string>)("test");
    std::cout << std::endl;
    PoKolei<int>(PoKolei<int>(print_val<int>, print_dashed<int>), print_usd<int>)(5);

    return 0;
}
