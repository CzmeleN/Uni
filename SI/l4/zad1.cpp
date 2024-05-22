#include <iostream>
#include <vector>

enum class Sign { black, white, empty };

class Board {
    public:
        static const short SIZE = 8;
        Sign board[SIZE][SIZE];

        Board() {
            for (short i = 0; i < SIZE; i++) {
                for (short j = 0; j < SIZE; j++) {
                    board[i][j] = Sign::empty;
                }
            }

            board[3][3] = board[4][4] = Sign::white;
            board[3][4] = board[4][3] = Sign::black;
        }

    void print() {
        for (short i = 0; i < SIZE; i++) {
            for (short j = 0; j < SIZE; j++) {
                if (board[i][j] == Sign::empty) {
                    std::cout << " . ";
                }
                else if (board[i][j] == Sign::black) {
                    std::cout << " B ";
                }
                else if (board[i][j] == Sign::white) {
                    std::cout << " W ";
                }
            }
            std::cout << std::endl;
        }
    }
};

struct Move {
    short x, y;
};

bool in_bounds(short x, short y) {
    if (x < 0 || x > 7 || y < 0 || y > 7) {
        return false;
    }
    return true;
}

Sign not_player(Sign player) {
    return player == Sign::black ? Sign::white : Sign::black;
}

std::vector<Move> gen_moves(const Board& board, Sign player) {
    std::vector<Move> res;
    Sign opposite = not_player(player);

    for (short i = 0; i < board.SIZE; i++) {
        for (short j = 0; j < board.SIZE; j++) {
            if (board.board[i][j] == player) {
                for (short dx : {-1, 0, 1}) {
                    for (short dy : {-1, 0, 1}) {
                        short new_x = i + dx;
                        short new_y = j + dy;

                        if (in_bounds(new_x, new_y) && board.board[i][j] == opposite) {
                            
                        }
                    }
                }
            }
        }
    }
    
    return res;
}


void make_move(Board& board, Move move, Sign player) {

}

int eval(const Board& board, Sign player) {
    return 0;
}

void minimax(Board& board, int depth, bool maximizing, Sign player, int alpha, int beta) {

}

Move random_move(const std::vector<Move>& moves) {
    return moves[rand() % moves.size()];
}

int main(int argc, char *argv[])
{
    srand(time(NULL));
    Board board;
    Sign curr_player = Sign::black;

    for (short i = 0; i < 1000; i++) {
    while (true) {
            std::vector<Move> legal_moves = gen_moves(board, curr_player);
            
            Move move = random_move(legal_moves);
            make_move(board, move, curr_player);
            curr_player = (curr_player == Sign::black) ? Sign::white : Sign::black;
        }
    }

    return 0;
}
