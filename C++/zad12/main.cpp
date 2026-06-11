#include <exception>
#include <iostream>
#include <functional>
#include <algorithm>
#include <stdexcept>
#include <deque>
#include <list>

template<typename T>
using fun = std::function<void(T)>;

template<typename T>
class Funktor {
private:
    T acc;
    T count;
public:
    Funktor() : acc(0), count(0) {};

    void operator() () const {
        if (count == 0) throw std::domain_error("nie zsumowano żadnych elementów");

        std::cout << "sum: " << acc << ", avg: " << acc / count << std::endl;
    }

    void operator() (const T x) noexcept {
        acc += x;
        count++;
    }

    void reset() noexcept {
        acc = 0;
        count = 0;
    }
};

template<typename T, typename Ti>
void test(Ti begin, const Ti& end) {
    Funktor<T> f;

    auto try_read = [&f](){
        try {
            f();
        } catch (std::exception& e) {
            std::cout << "złapano: " << e.what() << std::endl;
        }
    };

    try_read();

    std::for_each(begin, end, std::ref(f));
    try_read();

    f.reset();
    try_read();
}

int main() {
    std::vector<int> vec{-3, 0, 3, 14};

    auto y = std::bind(
        std::plus<int>(),
        std::bind(std::multiplies<int>(), std::placeholders::_1, 3),
        1
    );

    std::transform(vec.cbegin(), vec.cend(), vec.begin(), y);

    std::cout << "A)\n";

    for (auto i = vec.begin(); i < vec.end(); ++i) {
        std::cout << *i << (i == vec.end() - 1 ? '\n' : ' ');
    }

    std::cout << "\nB)\n" << "\ndeque<int>:\n";

    std::deque<int> deq{3, -4, 0, 5};
    test<int>(deq.begin(), deq.end());

    std::cout << "\nlist<double>:\n";

    std::list<double> li{3.4, -4.0, 0.1, 5.0};
    test<double>(li.begin(), li.end());

    return 0;
}
