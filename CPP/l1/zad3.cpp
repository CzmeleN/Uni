#include <iostream>
#include <stdint.h>

using namespace std;

enum class Name: uint16_t {
    Jan,
    Kacper,
    Kuba,
    Martyna,
    Milena,
    Laura
};

void message(string msg, Name name) {
    cout << msg << ", ";

    switch(name) {
        case Name::Jan:
            cout << "Jan";
            break;
        case Name::Kacper:
            cout << "Kacper";
            break;
        case Name::Kuba:
            cout << "Kuba";
            break;
        case Name::Martyna:
            cout << "Martyna";
            break;
        case Name::Milena:
            cout << "Milena";
            break;
        case Name::Laura:
            cout << "Laura";
            break;
    }

    cout << '.' << endl;
}

int main() {
    message("Cześć", Name::Jan);
    message("Hej", Name::Kacper);
    message("Witam", Name::Kuba);
    message("Uszanowanie", Name::Martyna);
    message("Siema", Name::Milena);
    message("Siemka", Name::Laura);

    return 0;
}
