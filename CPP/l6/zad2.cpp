#include <iostream>
#include <list>
#include <algorithm>
#include <random>

constexpr int N = 23;
constexpr int LONG_NAME = 5;
constexpr int DARK_LUM = 64;

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

    int get_name_len() const {
        return name.length();
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
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distriblen(1,10);
    std::uniform_int_distribution<> distribchar(0, 25);
    std::uniform_int_distribution<> distribpoint(0, 255);

    for (int i = 0; i < N; ++i) {
        int len = distriblen(gen);
        std::string name = "";

        for (int j = 0; j < len; ++j) {
            name += (char)(97 + distribchar(gen));
        }

        pl.push_back(Point(name, distribpoint(gen), distribpoint(gen), distribpoint(gen),
                     distribpoint(gen), distribpoint(gen)));
    }

    auto print_all = [&pl]() {
        std::cout << '\n';
        for (const auto& p : pl) std::cout << p;
        std::cout << std::endl;
    };

    std::erase_if(pl, [](Point x) {
        return x.get_name_len() > LONG_NAME;
    });

    std::cout << "Bez długich nazw\n";
    print_all();

    int freqs[5]{};

    std::for_each(pl.begin(), pl.end(), [&freqs](Point x) {
        freqs[x.get_quarter()]++;
    });

    std::cout << "Ćwiartki: ";

    for (int i = 0; i < 5; ++i) {
        std::cout << i << ": " << freqs[i] << '\n';
    }

    std::cout << '\n';

    pl.sort([](Point &a, Point &b) {
        return a.calc_lum() < b.calc_lum();
    });

    std::cout << "Posortowane po luminacji\n";
    print_all();

    std::list<Point> darks;

    std::for_each(pl.begin(), pl.end(), [&darks](Point x) {
        if (x.calc_lum() < DARK_LUM) darks.push_back(x);
    });

    std::cout << "Ciemne punkty\n";
    print_all();

    return 0;
}
