#include <iostream>
#include <vector>

using namespace std;

auto first_last(vector<int>& vec, const int k) {
    auto low = vec.begin();
    auto high = vec.end();

    while (low < high) {
        auto mid = low + (distance(low, high) / 2);

        if (const auto ans = (*mid <=> k); ans < 0) {
            low = mid + 1;
        } else {
            high = mid;
        }
    }

    auto first = low;

    high = vec.end();

    while (low < high) {
        auto mid = low + (distance(low, high) / 2);

        if (const auto ans = (k <=> *mid); ans < 0) {
            high = mid;
        } else {
            low = mid + 1;
        }
    }

    return pair{ first, low };
}

int main() {
    vector<int> vec = {1, 2, 3, 3, 4, 5, 5, 5, 6, 7, 7, 7, 7, 8, 9};

    auto [first, last] = first_last(vec, 5);

    cout << "ids: [" << distance(vec.begin(), first) << ", " << distance(vec.begin(), last) << ')' << endl;

    return 0;
}
