#include <iostream>
#include <forward_list>
#include <span>

// dla uproszczenia:
// możliwe tokeny:
// pojedyncze: ( ) + - * / = ! > <
// podwójne: <= >= == !=
// identyfikatory a-Z z _
// liczby 1-9 z max jedną kropką

enum class State {
    START,
    IDENT,
    EQ_COMP,
    OTHER_COMP,
    INT,
    FLOAT,
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

int main() {
    std::string test1 = "var x=5 const y = 4 fn sin   3 <= 4   x=3  4==4";

    std::forward_list<std::span<char>> res1;

    try {
        res1 = lexer(test1);
    } catch (size_t e) {
        std::cerr << "Incorrent lexer input @ " << e << '\n';
        std::cerr << test1 << '\n';
        for (size_t i = 0; i < e; ++i) std::cout << ' ';
        std::cerr << '^' << '\n';
        exit(1);
    }

    std::cout << test1 << "\n---\n";

    for (const auto& token: res1) {
        std::cout << std::string_view(token.data(), token.size()) << '\n';
    }

    return 0;
}
