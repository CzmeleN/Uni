#include <bits/stdc++.h>

using namespace std;

constexpr int N = 12;
constexpr int DIRS = 8;
constexpr int SIZE = N * N;
constexpr int DX[DIRS] = {-1, -1, -1, 0, 0, 1, 1, 1};
constexpr int DY[DIRS] = {-1, 0, 1, -1, 1, -1, 0, 1};

int backtrack(uint16_t board[], int n, int x) {
    uint16_t b;
    int res = 0;
    int nx, ny;

    for (int i = 0; i < n; ++i) {
        b = 1 << i;

        if ((board[x] & b) == 0) {
            if (x == n - 1) {
                return 1;
            }

            uint16_t new_board[SIZE];

            copy(board, board + n, new_board);

            //new_board[x] = 0xFFFF;
            new_board[x] |= b;

            for (int j = 0; j < DIRS; ++j) {
                nx = x + DX[j];
                ny = i + DY[j];

                while (nx >= 0 && ny >= 0 && nx < n && ny < n) {
                    new_board[nx] |= 1 << ny;
                    nx += DX[j];
                    ny += DY[j];
                }
            }

            res += backtrack(new_board, n, x + 1);
        }
    }

    return res;
}

int hetmans(int n) {
    uint16_t board[N] = {0};

    return backtrack(board, n, 0);
}

int main() {
    int n;
    
    cin >> n;
    cout << hetmans(n) << endl;
}
