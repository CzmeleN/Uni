#include "treap.hpp"
#include <iostream>
#include <ctime>

namespace ds = data_structures;

void display_menu() {
    std::cout << "\ndostępne opcje:\n";
    std::cout << "'i' insert\n";
    std::cout << "'r' remove\n";
    std::cout << "'s' search\n";
    std::cout << "'m' find min\n";
    std::cout << "'M' find max\n";
    std::cout << "'d' remove min\n";
    std::cout << "'D' remove max\n";
    std::cout << "'p' print\n";
    std::cout << "'t' test cp/mv\n";
    std::cout << "'x' wyjdź\n";
}

int main() {
    srand(time(nullptr));

    ds::Treap<int>* t = new ds::Treap<int>{15, 10, 20, 5}; 
    
    char c;
    int v;

    std::cout << "startowy: " << *t << "\n";

    auto print_type_var = [](){
        std::cout << "podaj wartość: ";
    };

    do {
        display_menu();

        if (!(std::cin >> c)) {
            break;
        }

        try {
            switch (c) {
                case 'i':
                    print_type_var();

                    std::cin >> v;

                    t->insert(v);

                    break;
                case 'r':
                    print_type_var();

                    std::cin >> v;

                    t->remove(v);

                    break;
                case 's':
                    print_type_var();

                    std::cin >> v;

                    std::cout << (t->search(v) ? "zawiera" : "nie zawiera") << "\n";

                    break;
                case 'm':
                    std::cout << "min: " << t->get_min() << "\n";

                    break;
                case 'M':
                    std::cout << "maks: " << t->get_max() << "\n";

                    break;
                case 'd':
                    t->remove_min();

                    break;
                case 'D':
                    t->remove_max();

                    break;
                case 'p':
                    std::cout << *t << "\n";

                    break;
                case 't': {
                    ds::Treap<int> copy(*t);

                    copy.insert(999);

                    std::cout << "kopia: " << copy << "\n";
                    std::cout << "og: " << *t << "\n";

                    ds::Treap<int> moved(std::move(copy));

                    std::cout << "kopia: " << copy << "\n";
                    std::cout << "moved: " << moved << "\n";

                    break;
                }
                case 'x':
                    break;
                default:
                    std::cout << "niepoprawna komenda\n";
            }
        } catch (const std::exception& e) {
            std::cout << "złapano: " << e.what() << "\n";
        }

    } while (c != 'x');

    delete t;

    return 0;
}
