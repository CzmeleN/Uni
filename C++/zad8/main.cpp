#include "array_utils.hpp"
#include <iostream>
#include <string>
#include <ctime>

class Person {
public:
    std::string name;
    int age;

    bool operator<(const Person& other) const {
        return age < other.age;
    }

    bool operator>(const Person& other) const {
        return age > other.age;
    }
};

std::ostream& operator<<(std::ostream& os, const Person& p) {
    return os << p.name << " - " << p.age;
}

int main() {
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    int nrs[] = {5, 2, 9, 1, 5, 6};
    int nrs_copy[6];
    arrcopy(nrs, 6, nrs_copy);

    std::cout << "og: ";
    arrprint(nrs, 6);

    arrpermut(nrs_copy, 6);
    std::cout << "perm (shuffled): ";
    arrprint(nrs_copy, 6);

    arrsort_quick(nrs_copy, 6);
    std::cout << "quicksort: ";
    arrprint(nrs_copy, 6);

    const char* makes[] = {"Bentley", "Aston-Martin", "Chevrolet", "Dodge"};
    const char* makes_copy[4];

    arrcopy(makes, 4, makes_copy);
    std::cout << "copied: "; arrprint(makes_copy, 4);

    arrsort_bubble(makes_copy, 4, greater<const char*>());
    std::cout << "reverse bubble: ";
    arrprint(makes_copy, 4);

    std::string words[] = {"now", "always", "later", "never"};

    arrsort_quick(words, 4);
    std::cout << "quicksort: ";
    arrprint(words, 4);

    Person people[] = { {"Ann", 25}, {"Peter", 18}, {"Eve", 30}, {"Juan", 22} };

    std::cout << "og: "; arrprint(people, 4);
    arrsort_bubble(people, 4);
    std::cout << "bubble: "; arrprint(people, 4);

    arrpermut(people, 4);
    std::cout << "shuffled: "; arrprint(people, 4);

    return 0;
}
