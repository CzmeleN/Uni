#include <iostream>
#include <tuple>
#include <ostream>

class Person {
private:
    static constexpr int HEAVY_KG = 100;
    std::string name;
    std::string surname;
    int age;
    int weight;
    double height;

public:
    Person(std::string n, std::string s, int a, int w, double h) :
        name(std::move(n)), surname(std::move(s)), age(a), weight(w), height(h) {
    };

    std::tuple<std::string, int, double> bmi_plus() const {
        return {std::format("{}{}", name[0], surname[0]), age, weight / (height * height)};
    }

    std::tuple<int, int, double> sizes() const {
        return {age, weight, height};
    }

    std::tuple<std::string, std::string, int> basic_info() const {
        return {name, surname, age};
    }
};

template <typename T, size_t... Is>
std::ostream& printTupleImp(std::ostream& os, const T& tp,
                       std::index_sequence<Is...>) {
    auto printElem = [&os](const auto& x, size_t id) {
        if (id > 0) os << ", ";
        os << id << ": " << x;
    };
    os << "(";
    (printElem(get<Is>(tp), Is), ...);
    os << ")";
    return os;
}
template <typename T, size_t TSize = std::tuple_size<T>::value>
std::ostream& operator <<(std::ostream& os, const T& tp) {
    return printTupleImp(os, tp,
                         std::make_index_sequence<TSize>{});
}

int main() {
    Person p("Jan", "Mączyński", 21, 87, 1.89);

    const auto [initials, age, bmi] = p.bmi_plus();

    std::cout << initials << ' ' << age << ' ' << bmi << '\n';

    const auto tup1 = p.sizes();
    std::cout << tup1 << '\n';

    // std::cout << std::get<0>(tup1) << ' ' << std::get<1>(tup1) << ' ' << 
    //     std::get<2>(tup1) << '\n';

    const auto tup2 = p.basic_info();
    std::cout << tup2 << '\n';

    // std::cout << std::get<0>(tup2) << ' ' << std::get<1>(tup2) << ' ' << 
    //     std::get<2>(tup2) << '\n';

    return 0;
}
