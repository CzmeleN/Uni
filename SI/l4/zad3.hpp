#include <bits/stdc++.h>

enum Player { big, small };
enum Field { field, trap, dam, river };
enum Animal { rat, cat, dog, wolf, panther, tiger, lion, elephant, none };
static const short MAX_THREADS = 12;
static const short ROWS = 9;
static const short COLS = 7;
static const short FIGURES_CT = 8;
static const std::pair<int, int> dirs[4] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
// static const short DEPTH = 5;
// static const short GAMES = 1000;

struct Move {
    std::pair<short, short> cord;
    std::pair<short, short> directs;
};

const Field BACKGROUND[ROWS][COLS] = {
    {field, field, trap, dam, trap, field, field},
    {field, field, field, trap, field, field, field},
    {field, field, field, field, field, field, field},
    {field, river, river, field, river, river, field},
    {field, river, river, field, river, river, field},
    {field, river, river, field, river, river, field},
    {field, field, field, field, field, field, field},
    {field, field, field, trap, field, field, field},
    {field, field, trap, dam, trap, field, field},
};

struct Node {
    Player to_move;
    std::vector<std::vector<int>> board;
    std::vector<Animal> small_poses, big_poses;

    Node();

    void copy(const Node& node);
    void make_move(const Move& move);
    void print();
    std::vector<Move> gen_moves();
};

bool in_bounds(short x, short y);
Player not_player(Player player);