#include <cstdint>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Osoba {
public:
    string name;
    string surname;
    uint16_t birth_year;

    Osoba(string name, string surname, uint16_t birth_year) {
        this->name = name;
        this->surname = surname;
        this->birth_year = birth_year;
    }

    friend bool operator<(const Osoba& a, const Osoba& b) {
        return tie(a.surname, a.name, a.birth_year) < tie(b.surname, b.name, b.birth_year);
    }
};

int main() {
    vector<Osoba> osoby = {
        Osoba("Jan", "Maczynski", 2004),
        Osoba("Jake", "Smith", 2005),
        Osoba("Jake", "Smith", 1998),
        Osoba("Juan", "Pal", 1999),
        Osoba("Pablo", "Smith", 1999)
    };

    sort(osoby.begin(), osoby.end());

    for (auto osoba: osoby) {
        cout << osoba.surname << ' ' << osoba.name << ' ' << osoba.birth_year << endl;
    }

    return 0;
}
