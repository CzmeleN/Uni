#include <algorithm>
#include <iostream>
#include <deque>
#include <vector>

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

    double calc_bmi() const {
        return (double)weight / (height * height);
    }

    void reduce(double frac) {
        weight = (double)weight * (1.0 - frac);
    }

    bool is_heavy() const {
        return weight >= HEAVY_KG;
    }

    int get_weight() const {
        return weight;
    }

    friend std::ostream& operator<<(std::ostream& os, const Person &x) {
        os << x.name << ' ' << x.surname << ' ' << x.age << ' ' << x.weight << ' '
            << x.height << '\n';
        return os;
    }
};

int main() {
    std::deque<Person> pd = {
        Person("Jan", "Mączyński", 21, 87, 1.89),
        // wygenerowani ludzie
        Person("Anna", "Nowak", 25, 60, 1.65),
        Person("Jan", "Kowalski", 34, 85, 1.82),
        Person("Piotr", "Wiśniewski", 41, 92, 1.78),
        Person("Katarzyna", "Wójcik", 29, 55, 1.70),
        Person("Michał", "Kamiński", 52, 98, 1.75),
        Person("Agnieszka", "Lewandowska", 19, 50, 1.62),
        Person("Tomasz", "Zieliński", 38, 88, 1.90),
        Person("Magdalena", "Szymańska", 27, 58, 1.68),
        Person("Paweł", "Woźniak", 45, 102, 1.80),
        Person("Monika", "Dąbrowska", 31, 63, 1.72),
        Person("Krzysztof", "Jankowski", 60, 89, 1.76)
    };

    auto print_all = [&pd]() {
        std::cout << '\n';
        for (auto const& p : pd) std::cout << p;
        std::cout << std::endl;
    };
    
    std::cout << "posortowani po BMI:\n";

    std::sort(pd.begin(), pd.end(), [](Person x, Person y) {
        return x.calc_bmi() < y.calc_bmi();
    });

    print_all();

    std::cout << "odchudzeni wypisani:\n";

    std::for_each(pd.begin(), pd.end(), [](Person x) {
        x.reduce(0.1);
    });

    print_all();

    std::vector<Person> heavies, lights;

    std::for_each(pd.begin(), pd.end(), [&heavies, &lights](Person x) {
        if (x.is_heavy()) heavies.push_back(x);
        else lights.push_back(x);
    });

    bool first = true;

    for (auto const& v : {heavies, lights}) {
        std::cout << (first ? "ciężcy" : "leccy") << '\n';
        first = false;

        for (auto const& p : v) std::cout << p;
        std::cout << std::endl;
    }

    auto cmp = [](Person x, Person y) {
        return x.get_weight() < y.get_weight();
    };

    std::cout << "najcięższy: "
        << *std::max_element(pd.begin(), pd.end(), cmp)
        << "najlżejszy: "
        << *std::min_element(pd.begin(), pd.end(), cmp) << std::endl;
}
