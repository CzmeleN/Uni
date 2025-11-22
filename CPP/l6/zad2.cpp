#include <iostream>
#include <list>
#include <algorithm>

constexpr int N = 23;

class Point {
private:
    static constexpr double DARK_LUM = 64.0;
    std::string name;
    int x;
    int y;
    int r;
    int g;
    int b;
public:
    Point(std::string n, int nx, int ny, int nr, int ng, int nb) :
        name(std::move(n)), x(nx), y(ny), r(nr), g(ng), b(nb) {
    };

    double calc_lum() const {
        return (double)r * 0.3 + (double)g * 0.59 + (double)b * 0.11;
    }

    int get_quarter() const {
        if (x > 0) {
            if (y > 0) {
                return 1;
            } else if (y < 0) {
                return 4;
            }
        } else if (x < 0) {
            if (y > 0) {
                return 2;
            } else if (y < 0) {
                return 3;
            }
        }
        return 0;
    }

    bool is_dark() const {
        return calc_lum() < DARK_LUM;
    }

    friend std::ostream& operator<<(std::ostream& os, const Point &x) {
        os << x.name << ' ' << x.x << ' ' << x.y << ' ' << x.r << ' ' << x.g
            << ' ' << x.b << '\n';
        return os;
    }
};

int main() {
    std::list<Point> pl;

    srand(time(NULL));

    for (int i = 0; i < N; ++i) {
        int len = rand() % 11;
        std::string name = "";

        for (int j = 0; j < len; ++j) {

        }
    }

    auto print_all = [&pl]() {
        std::cout << '\n';
        for (const auto& p : pl) std::cout << p;
        std::cout << std::endl;
    };


}
