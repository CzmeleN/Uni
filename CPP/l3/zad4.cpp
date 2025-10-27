#include <iostream>

using namespace std;

template<typename Ts, typename Td>
void my_move (Ts &&src, Td &dst) {
    if constexpr (is_pointer_v<Ts>) {
        static_assert(is_convertible_v<remove_pointer_t<Ts>, Td>, "not convertible");
        dst = std::move(*src);
    } else {
        static_assert(is_convertible_v<Ts, Td>, "not convertible");
        dst = std::move(src);
    }
}

struct test {
    int x;
};

int main() {
    int x = 1;
    long long y = 0;

    my_move(x, y);
    x = 2;
    cout << " (expected: 1) " << y << endl;

    my_move(&x, y);
    x = 3;
    cout << "(expected: 2) " << y << endl;

    string one = "test";
    string two = "";

    my_move(one, two);
    cout << one << " two: " << two << endl;

    one = "one";
    two = "";

    my_move(&one, two);
    cout << one << " two: " << two << endl;

    // nie skompiluje się
    // test z;
    // my_move(x, z);

    return 0;
}
