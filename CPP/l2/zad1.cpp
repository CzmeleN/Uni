#include <stdint.h>
#include <iostream>
#include <memory>
#include <random>
#include <utility>

using namespace std;

constexpr size_t N = 40;
constexpr size_t M = 20;

class One {
private:
    uint64_t cnt = 1;

public:
    virtual ~One() {
        cerr << "destr, cnt: " << cnt << endl;
    }

    void add(uint64_t x) {
        cnt += x; 
    }

    uint64_t get() {
        return cnt;
    }
};

using TabPtr = unique_ptr<One, void(*)(One*)>;

TabPtr fun(TabPtr tab, uint64_t cnt) {
    if (cnt >= M) return tab;

    static array<size_t, N> ids = [](){
        array<size_t, N> t;

        for (size_t i = 0; i < N; ++i) {
            t[i] = i;
        }

        return t;
    }();
    static random_device rd;
    static mt19937 gen(rd());

    shuffle(ids.begin(), ids.end(), gen);

    for (size_t i = 0; i < N / 10; ++i) {
        tab.get()[ids[i]].add(cnt);
    }

    return fun(move(tab), cnt + 1);
}

int main() {
    TabPtr tab(
        new One[N],
        [] (One* tab) { delete[] tab; }
    );

    tab = fun(move(tab), 0);

    for (size_t i = 0; i < N; ++i) {
        cout << "id: " << i << ", cnt: " << tab.get()[i].get() << endl;
    }

    return 0;
}

