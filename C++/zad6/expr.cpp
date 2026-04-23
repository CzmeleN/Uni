#include "expr.hpp"
#include <stdexcept>
#include <algorithm>

namespace expression_tree {

constexpr int MAX_PRIO = 10;
constexpr int NOT_PRIO = 9;
constexpr int AND_PRIO = 5;
constexpr int XOR_PRIO = 4;
constexpr int OR_PRIO = 3;
constexpr int IMP_PRIO = 2;
constexpr int EQV_PRIO = 1;

lit::lit(bool v) : val(v) {}

lit lit::TRUE(true);

lit lit::FALSE(false);

bool lit::calc() const {
    return val;
}

std::string lit::print() const {
    return val ? "1" : "0";
}
int lit::get_prio() const {
    return MAX_PRIO;
}

std::vector<std::pair<std::string, bool>> var::vars;

var::var(std::string n) : name(n) {
    for (char c : n) {
        if (c < 'a' || c > 'z') throw std::invalid_argument("nazwa musi skladać się tylko z małych liter");
    }
}

bool var::calc() const {
    for (const auto& p : vars) {
        if (p.first == name) return p.second;
    }

    throw std::runtime_error("niestniejąca zmienna: " + name);
}

std::string var::print() const {
    return name;
}

int var::get_prio() const {
    return MAX_PRIO;
}

void var::add(const std::string& n, bool v) {
    for (const auto& p : vars) {
        if (p.first == n) throw std::logic_error("zmienna już istnieje: " + n);
    }

    vars.push_back({n, v});
}

void var::rm(const std::string& n) {
    vars.erase(std::remove_if(vars.begin(), vars.end(),
               [&](const std::pair<std::string, bool>& p) {
                              return p.first == n;
                              }), vars.end());
}

void var::set(const std::string& n, bool v) {
    for (auto& p : vars) {
        if (p.first == n) {
            p.second = v;
            return;
        }
    }

    throw std::runtime_error("niestniejąca zmienna: " + n);
}

uop::uop(expr* c) : child(c) {}

uop::~uop() {
    delete child;
}

bop::bop(expr* l, expr* r) : left(l), right(r) {}

bop::~bop() { delete left; delete right; }

std::string bop::print_child(expr* child, bool is_right) const {
    int my_prio = this->get_prio();
    int child_prio = child->get_prio();

    if (child_prio < my_prio || (child_prio == my_prio && is_right))
        return "(" + child->print() + ")";

    return child->print();
}

bool not_op::calc() const {
    return !child->calc();
}

std::string not_op::print() const {
    std::string cp = child->print();

    if (child->get_prio() < get_prio()) return "!(" + cp + ")";

    return "!" + cp;
}

int not_op::get_prio() const {
    return NOT_PRIO;
}

bool and_op::calc() const {
    return left->calc() && right->calc();
}

std::string and_op::print() const {
    return print_child(left, false) + " & " + print_child(right, true);
}

int and_op::get_prio() const {
    return AND_PRIO;
}

bool xor_op::calc() const {
    return left->calc() != right->calc();
}

std::string xor_op::print() const {
    return print_child(left, false) + " ^ " + print_child(right, true);
}

int xor_op::get_prio() const {
    return XOR_PRIO;
}

bool or_op::calc() const {
    return left->calc() || right->calc();
}

std::string or_op::print() const {
    return print_child(left, false) + " | " + print_child(right, true);
}

int or_op::get_prio() const {
    return OR_PRIO;
}

bool imp_op::calc() const {
    return !left->calc() || right->calc();
}

std::string imp_op::print() const {
    return print_child(left, false) + " => " + print_child(right, true);
}

int imp_op::get_prio() const {
    return IMP_PRIO;
}

bool eqv_op::calc() const {
    return left->calc() == right->calc();
}

std::string eqv_op::print() const {
    return print_child(left, false) + " <=> " + print_child(right, true);
}

int eqv_op::get_prio() const {
    return EQV_PRIO;
}

}
