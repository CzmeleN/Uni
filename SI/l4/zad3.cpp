#include "zad3.hpp"
#include <vector>

Node::Node() {
    std::vector<std::vector<Animal>> board(ROWS, std::vector<Animal>(COLS, Animal::none));
    std::vector<Animal> small_poses(FIGURES_CT), big_poses(FIGURES_CT);
}

void Node::copy(const Node& node) {
    to_move = not_player(node.to_move);
    board = node.board;
    small_poses = node.small_poses;
    big_poses = node.big_poses;
}

void Node::make_move(const Move& move) {

}

void Node::print() {

}

std::vector<Move> Node::gen_moves() {
    std::vector<Move> res;

    for (short an = Animal::rat; an < Animal::none; an++) {
        for (const auto& dir : dirs) {
            short new_x = dir.first, new_y = dir.second;

            if (to_move == Player::small) {
                new_x += small_poses[an];
                new_y += small_poses[an];
            }
            else {
                new_x += big_poses[an];
                new_y += big_poses[an];
            }

            if (in_bounds(new_x, new_y)) {

            }
        }
    }

}

bool in_bounds(short x, short y) {
    if (x < 0 || x > COLS || y < 0 || y > ROWS) {
        return false;
    }

    return true;
}

Player not_player(Player player) {
    return player == Player::big ? Player::small : Player::big;
}

int main(int argc, char *argv[])
{
    Board board;
    Node* starting;
    Node* root;
    Node* best_node = nullptr;
    bool possible = false, skipped = false;
    std::pair<short, short> wins = {0, 0};
    Sign mm_sign;
    short move_ct;

    srand(time(NULL));
    
    for (int i = 0; i < GAMES; i++) {
        root = new Node(board, Sign::black);
        starting = root;
        mm_sign = rand() % 2 ? Sign::white : Sign::black;
        move_ct = 0;

        while (true) {
            possible = root->gen_children();

            if (!possible) {
                if (skipped) {
                    if (fin_eval(root->board, mm_sign)) {
                        wins.first++;
                    }
                    else {
                        wins.second++;
                    }
                    break;
                }

                skipped = true;
            }
            else {
                skipped = false;
            }

            if (root->to_move == mm_sign) {
                best_node = best_move(root, move_ct);
                // best_node = random_move(root);
            }
            else {
                best_node = random_move(root);
            }
            
            root = best_node;
            move_ct++;
        }

        std::cout << "Minimax #wins: " << wins.first << " Random #wins: " << wins.second << std::endl;
        delete starting;
    }

    return 0;
}
