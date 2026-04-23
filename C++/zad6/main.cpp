#include "expr.hpp"
#include <iostream>

using namespace expression_tree;

int main() {
    var::add("p", false);
    var::add("q", true);

    expr* e1 = new eqv_op(
        new imp_op(new var("p"), new var("q")),
        new not_op(new imp_op(new var("q"), new var("p")))
    );

    expr* e2 = new eqv_op(
        new not_op(new imp_op(new var("p"), new var("q"))),
        new and_op(new var("p"), new not_op(new var("q")))
    );

    expr* e3 = new imp_op(
        new eqv_op(new and_op(new var("p"), new lit(true)), new var("p")),
        new eqv_op(new or_op(new var("p"), new lit(false)), new var("p"))
    );

    expr* e4 = new imp_op(
        new or_op(new var("p"), new var("q")),
        new imp_op(new var("p"), new var("q"))
    );

    expr* exprs[] = { e1, e2, e3, e4 };

    for (int i = 0; i < 4; ++i) {
        std::cout << "print: " << exprs[i]->print() << std::endl;
        std::cout << "calc: " << exprs[i]->calc() << '\n' << std::endl;

        delete exprs[i];
    }

    return 0;
}
