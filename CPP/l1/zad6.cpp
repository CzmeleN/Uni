#include <iostream>
#include <sstream>
#include <algorithm>

using namespace std;
using uint = unsigned int;

int main() {
    string input;

    cout << "DD.MM.YYYY" << endl;
    cin >> input;

    replace(input.begin(), input.end(), '.', ' ');
    
    istringstream iss(input);
    uint day, month, year;

    iss >> day >> month >> year;

    cout << day << ' ';

    switch(uint m = month; m) {
        case 1:
            cout << "stycznia";
            break;
        case 2:
            cout << "lutego";
            break;
        case 3:
            cout << "marca";
            break;
        case 4:
            cout << "kwietnia";
            break;
        case 5:
            cout << "maja";
            break;
        case 6:
            cout << "czerwca";
            break;
        case 7:
            cout << "lipca";
            break;
        case 8:
            cout << "sierpnia";
            break;
        case 9:
            cout << "września";
            break;
        case 10:
            cout << "października";
            break;
        case 11:
            cout << "listopada";
            break;
        case 12:
            cout << "grudnia";
            break;
        default:
            cout << "(wrong month)";
            break;
    }

    cout << ' ' << year << endl;

    return 0;
}
