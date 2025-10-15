#include "csapp.h"

ssize_t Rio_writen(int fd, const void *usrbuf, size_t n);

static int ndselect(int n) {
    for (int i = 0; i < n; ++i) {
        pid_t pid = fork(); // u rodzica zwróci pid dziecka, w dziecku 0

        if (pid == 0) { 
            return i; // w dziecku wrócimy do main
        }

        // waitpid(pid, NULL, 0);
    }

    for (int i = 0; i < n; ++i) {
        waitpid(-1, NULL, 0); // -1 oznacza, że na dowolne dziecko
    }

    exit(0);
}

static int conflict(int x1, int y1, int x2, int y2) {
    return x1 == x2
    || y1 == y2
    || x1 + y1 == x2 + y2
    || x1 - y1 == x2 - y2;
}

static void print_line_sep(int size) {
    for (int i = 0; i < size; ++i) 
        printf("+---");
    printf("+\n");
}

static void print_board(int size, int board[size]) {
    for (int i = 0; i < size; ++i) {
        print_line_sep(size);
        for (int j = 0; j < size; ++j)
            printf("|%s", board[i] == j ? " Q " : "   ");
        printf("|\n");
    }
    print_line_sep(size);
    printf("\n");
}

static void a_print_line_sep(int size, char *buff, size_t *len) {
    for (int i = 0; i < size; ++i) 
        *len += sprintf(buff + *len, "+---");
    *len += sprintf(buff + *len, "+\n");
}

static void a_print_board(int size, int board[size]) {
    char buff[2048];
    size_t off = 0;

    for (int i = 0; i < size; ++i) {
        a_print_line_sep(size, buff, &off);
        for (int j = 0; j < size; ++j)
            off += sprintf(buff + off, "|%s", board[i] == j ? " Q " : "   ");
        off += sprintf(buff + off, "|\n");
    }
    a_print_line_sep(size, buff, &off);
    off += sprintf(buff + off, "\n");

    Rio_writen(STDOUT_FILENO, buff, off);
}

int main(int argc, char **argv) {
    if (argc != 2)
        app_error("Usage: %s [SIZE]", argv[0]);

    int size = atoi(argv[1]);

    if (size < 3 || size > 9)
        app_error("Give board size in range from 4 to 9!");

    int board[size];

    for (int i = 0; i < size; ++i) {
        int j = ndselect(size);

        board[i] = j;

        for (int j = 0; j < i; ++j) {
            if (conflict(i, board[i], j, board[j])) {
                exit(0);
            }
        }
    }

    a_print_board(size, board);

    return 0;
}
