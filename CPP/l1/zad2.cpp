#include <iostream>
#include <set>

using namespace std;

using SetS = set<string>;

int main() {
    SetS ss = {"one", "two", "three"};

    for (const auto& s: ss) {
        cout << s << endl;
    }

    return 0;
}
