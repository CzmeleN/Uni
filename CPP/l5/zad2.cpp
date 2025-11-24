#include <iostream>
#include <forward_list>
#include <span>
#include <unordered_map>
#include <map>
#include <deque>
#include <stack>

// dla uproszczenia:
// możliwe tokeny:
// pojedyncze: ( ) + - * / = ! > <
// podwójne: <= >= == !=
// identyfikatory a-Z z _
// liczby 1-9 z max jedną kropką
// funkcje wbudowane: sin i cos
// zapisane stałe: pi, e

enum class State {
    START,
    IDENT,
    EQ_COMP,
    OTHER_COMP,
    INT,
    FLOAT,
};

enum class SType {
    L_BR,
    R_BR,
    OPER,
    CONST,
    NUM,
    VAR,
    FUN
};

struct Symbol {
    SType type;
    double val = 0.0;
    std::string id;
    int prio = 0;
};

constexpr bool is_ident(char c) {
    return std::isalpha(c) || c == '_';
}

constexpr bool can_start_symbol(char c) {
    return c == '!' || c == '<' || c == '>';
}

constexpr bool is_singular(char c) {
    return c == '(' || c == ')' || c == '+' || c == '-' || c == '*' || c == '/';
}

std::forward_list<std::span<char>> lexer(std::string &s) {
    std::forward_list<std::span<char>> list{};
    auto it = list.before_begin();
    size_t first = 0;
    State state = State::START;

    auto save_token = [&](size_t end) {
        it = list.insert_after(it, std::span<char>(&s[first], &s[end]));
    };

    auto save_start= [&](size_t pos) {
        save_token(pos);
        state = State::START;
    };

    for (size_t pos = 0; pos < s.length(); ++pos) {
        char c = s[pos];

        if (std::isspace(c)) {
            if (state != State::START) save_start(pos);
            continue;
        }

        // nawiasy lub operatory nie wymagają spacji oddzielającej
        if (is_singular(c)) {
            if (state != State::START) save_start(pos);

            first = pos;
            save_token(pos + 1);

            continue;
        }

        if (state != State::EQ_COMP && state != State::OTHER_COMP) {
            if (can_start_symbol(c) || c == '=') {
                if (state != State::START) save_start(pos);

                first = pos;
                if (c == '=') {
                    state = State::EQ_COMP;
                } else {
                    state = State::OTHER_COMP;
                }

                continue;
            }
        } else if (!can_start_symbol(c) && c != '='){
            save_start(pos);
        }

        switch (state) {
            case State::INT:
                if (std::isdigit(c)) continue;
                if (c == '.') state = State::FLOAT;
                break;
            case State::FLOAT:
                if (std::isdigit(c)) continue;
                break;
            case State::IDENT:
                if (is_ident(c)) continue;
                break;
            case State::OTHER_COMP:
                [[fallthrough]];
            case State::EQ_COMP:
                if (c == '=') {
                    save_start(pos + 1);
                    continue;
                }
                break;
            case State::START:
                first = pos;

                if (std::isdigit(c)) state = State::INT;
                else if (is_ident(c)) state = State::IDENT;
                else if (can_start_symbol(c)) state = State::OTHER_COMP;
                else if (c == '=') state = State::EQ_COMP;
                else break;

                continue;
        }

        throw pos;
    }

    if (state != State::START) save_token(s.length());

    return list;
}

constexpr int get_prio(const std::string &op) {
    if (op == "sin" || op == "cos") return 3;
    if (op == "*" || op == "/") return 2;
    if (op == "+" || op == "-") return 1;
    if (op == "=" || op == "==" || op == "<=" || op == ">=" || op == "!" || op == "!=") return 0;
    return -1;
}

std::forward_list<Symbol> to_symbols(const std::forward_list<std::span<char>> &tks) {
    std::forward_list<Symbol> list{};
    auto it = list.before_begin();

    std::map<std::string, double> consts {{"pi", 3.14}, {"e", 2.71}};
    std::unordered_map<std::string, double> vars{};
    std::deque<std::string> funs{"sin", "cos", "+", "-", "*", "/", "=", "==", "<=", ">=", "<", ">", "!=", "!"};

    for (const auto &tk : tks) {
        std::string txt(tk.data(), tk.size());
        Symbol s;

        if (txt == "(") {
            s.type = SType::L_BR;
            s.id = "(";
        } else if (txt == ")") {
            s.type = SType::R_BR;
            s.id = ")";
        } else if (consts.contains(txt)) {
            s.type = SType::CONST;
            s.id = txt;
            s.val = consts[txt];
        } else if (std::find(funs.begin(), funs.end(), txt) != funs.end()) {
            s.prio = get_prio(txt);
            s.type = s.prio >= 3 ? SType::FUN : SType::OPER;
            s.id = txt;
        } else if (std::isdigit(txt[0])) {
            s.type = SType::NUM;
            s.val = std::stod(txt);
        } else {
            s.type = SType::VAR;
            s.id = txt;
        }

        it = list.insert_after(it, s);
    }

    return list;
}

std::forward_list<Symbol> dijkstra(const std::forward_list<Symbol> &ss) {
    std::forward_list<Symbol> list{};
    auto it = list.before_begin();

    auto save = [&](Symbol s) {
        it = list.insert_after(it, s);
    };

    std::stack<Symbol> stack;

    for (const auto &s : ss) {
        if (s.type == SType::NUM || s.type == SType::VAR || s.type == SType::CONST) {
            save(s);
        } else if (s.type == SType::FUN) {
            stack.push(s);
        } else if (s.type == SType::OPER) {
            while (!stack.empty()) {
                const auto &top = stack.top();

                if (top.type == SType::L_BR) break;

                bool right = (s.id == "="); 

                if ((!right && s.prio <= top.prio) || (right && s.prio < top.prio)) {
                    save(top);
                    stack.pop();
                } else {
                    break;
                }
            }

            stack.push(s);
        } else if (s.type == SType::L_BR) {
            stack.push(s);
        } else if (s.type == SType::R_BR) {
            bool found_left = false;

            while (!stack.empty()) {
                Symbol top = stack.top();
                stack.pop();

                if (top.type == SType::L_BR) {
                    found_left = true;
                    break;
                } else {
                    save(top);
                }
            }

            if (!found_left) {
                throw 1;
            }

            if (!stack.empty() && stack.top().type == SType::FUN) {
                save(stack.top());
                stack.pop();
            }
        }
    }

    while (!stack.empty()) {
        Symbol top = stack.top();

        if (top.type == SType::L_BR || top.type == SType::R_BR) {
            throw 1;
        }

        save(top);
        stack.pop();
    }

    return list;
}

void print_symbols(const std::forward_list<Symbol>& ss) {
    for (const auto &s : ss) {
        if (s.type == SType::NUM) std::cout << s.val << ' ';
        else if (s.type == SType::CONST) std::cout << s.id << '(' << s.val << ") ";
        else std::cout << s.id << ' ';
    }
    std::cout << '\n';
}

int main() {
    std::string test = "sin(x) + 2 * 3";

    std::forward_list<std::span<char>> res1;

    try {
        res1 = lexer(test);
    } catch (size_t e) {
        std::cerr << "Incorrent lexer input @ " << e << '\n';
        std::cerr << test << '\n';
        for (size_t i = 0; i < e; ++i) std::cout << ' ';
        std::cerr << '^' << '\n';
        exit(1);
    }

    std::forward_list<Symbol> symbols = to_symbols(res1);
    std::cout << "Normal: ";
    print_symbols(symbols);

    std::forward_list<Symbol> post;
    try {
        post = dijkstra(symbols);
    } catch (int e) {
        std::cerr << "Mismatched parentheses\n";
        exit(2);
    }
    std::cout << "Postfix: ";
    print_symbols(post);

    return 0;
}
