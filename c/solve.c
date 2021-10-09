#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define get_index(x, y) (9*(x)+(y))

struct board {
    int board[81];
};

static bool legal_counts(int *counts) {
    for (int i = 1; i < 10; i++)
        if (counts[i] > 1)
            return false;
    return true;
}

static bool legal_board(int *board) {
    for (int i = 0; i < 9; i++) {
        int row_digit_counts[10] = {0};
        int col_digit_counts[10] = {0};

        for (int j = 0; j < 9; j++) {
            row_digit_counts[board[get_index(i,j)]]++;
            col_digit_counts[board[get_index(j,i)]]++;
        }

        if (!legal_counts(row_digit_counts) || !legal_counts(col_digit_counts))
            return 0;
    }

    for (int i = 0; i < 9; i++) {
        int box_digit_counts[10] = {0};

        for (int j = 0; j < 81; j++)
            if (3*(j/27)+(j%9)/3 == i)
                box_digit_counts[board[j]]++;
        if (!legal_counts(box_digit_counts))
            return 0;
    }

    return 1;
}

static int get_empty_position(int *board) {
    for (int i = 0; i < 81; i++)
        if (board[i] == 0)
            return i;
    return -1;
}

static bool solve(struct board *board) {
    int current_pos = get_empty_position(board->board);
    if (current_pos == -1) {
        return true;
    }
    for (int d = 1; d <= 9; d++) {
        board->board[current_pos] = d;
        if (legal_board(board->board)) {
            struct board temp = *board;
            if (solve(&temp)) {
                *board = temp;
                return true;
            }
        }
    }
    return false;
}

static void print(struct board *board) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            printf("%d", board->board[get_index(i,j)]);
        }
        printf("\n");
    }
}

int main() {
    struct board board;
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    int puzzle[81] = {0};
    fp = fopen("../sudoku_puzzles", "r");
    if (fp == NULL) exit(EXIT_FAILURE);
    while (getline(&line, &len, fp) != -1) {
        for (int i = 0; i < 81; i++) puzzle[i] = line[i] - '0';
        memcpy(board.board, puzzle, sizeof(puzzle));
        solve(&board);
        print(&board);
        printf("\n");
    }
    return 0;
}
