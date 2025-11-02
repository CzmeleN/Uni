#include <iostream>
#include <vector>
#include <set>
#include <list>

int main() {
    auto first_elem = []<typename T>(const T& xs) {
        if (xs.empty()) {
            return typename T::value_type{};
        }

        return *xs.begin();
    };

    std::vector<int> vec{13, 1};
    std::list<std::string> list{"jeden", "dwa"};
    std::set<double> e_set;

    std::cout << first_elem(vec) << '\n' << first_elem(list) << '\n' << first_elem(e_set) << std::endl;

    return 0;
}
