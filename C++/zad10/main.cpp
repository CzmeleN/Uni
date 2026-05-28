#include <algorithm>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <cstdlib>
#include <vector>
#include <string>
#include "A.hpp"
#include "B.hpp"

void append_lorem(const std::string& name) {
    std::ofstream out(name);

    out << "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat.\nDuis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur.\nExcepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.";
}

void test_a() {
    std::istringstream iss("start zostanie usunięte\ntest 1234567\n");
    std::string s1, s2, s3;

    iss >> s1 >> clearline;
    iss >> s2 >> ignore(5);
    iss >> s3;

    std::cout << index(1, 2) << colon << s1 << comma <<
              index(2, 2) << colon << s2 << comma <<
              index(3, 2) << colon << s3 << "\n\n";

    const std::string txt_file = "test_a.txt";
    append_lorem(txt_file);

    std::ifstream f(txt_file);
    std::vector<std::pair<int, std::string>> lines;
    std::string line;

    int line_number = 1;

    while (std::getline(f, line)) {
        lines.push_back({line_number++, line});
    }

    std::sort(lines.begin(), lines.end(), [](const auto& a, const auto& b) {
        return a.second < b.second;
    });

    for (const auto& item : lines) {
        std::cout << index(item.first, 3) << colon << item.second << '\n';
    }

    std::cout << "\n-----\n\n";
}

void test_b() {
    const std::string fn1 = "test1.bin";
    const std::string fn2 = "test2.bin";
    int x;

    {
        ofsbin out(fn1);

        std::cout << "wylosowane liczby:\n\n";

        for (int i = 0; i < 10; ++i) {
            x = rand() % 100;

            out.write(x);

            std::cout << x << '\n';
        }
    }

    try {
        ifsbin in(fn1);

        std::cout << "\nodczytane lizcby:\n\n";

        while (true) {
            in.read(x);

            std::cout << x << '\n';
        }
    } catch (const std::ios_base::failure& e) {
        std::cout << "\nzłapano oczekiwany failure\n\n";
    }

    char dir1 = 'N', dir2 = 'E';
    int deg1 = 51, deg2 = 17, min1 = 6, min2 = 3;
    double sec1 = 39.4, sec2 = 12.1;

    {
        ofsbin out(fn2);

        out.write(dir1).write(deg1).write(min1).write(sec1);
        out.write(dir2).write(deg2).write(min2).write(sec2);
    }

    {
        ifsbin in(fn2);

        in.read(dir1).read(deg1).read(min1).read(sec1);
        in.read(dir2).read(deg2).read(min2).read(sec2);

        std::cout << dir1 << " " << deg1 << "* " << min1 << "' " << sec1 <<
                  "\"\n" << dir2 << " " << deg2 << "* " << min2 << "' " <<
                  sec2 << "\"\n\n";
    }

    try {
        ifsbin in(fn2);

        while (true) {
            unsigned char b;
            in.read(b);

            std::cout << "0x" << std::hex << std::setw(2) << std::setfill('0')
                      << (int)b << std::dec << std::setfill(' ') << '\t' <<
                      std::setw(3) << (int)b;

            if (b >= 32 && b <= 126) {
                std::cout << '\t' << (char)b;
            }

            std::cout << '\n';
        }
    } catch (const std::ios_base::failure&) {
        std::cout << "\nzłapano oczekiwany failure\n";
    }
}

int main() {
    srand(time(NULL));

    test_a();
    test_b();

    return 0;
}
