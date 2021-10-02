#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool legal_counts(int* counts) {
    int max = 0;
    for (int i = 1; i < 10; i++) {
        max = (max < counts[i]) ? counts[i] : max;
    }
    return (max <= 1);
}

int get_index(int x, int y) {
    return 9*x+y;
}

bool legal_board(int* board) {
    for (int i = 0; i < 9; i++) {
        int row_digit_counts[10];
        int col_digit_counts[10];
        memset(row_digit_counts, 0, sizeof(row_digit_counts));
        memset(col_digit_counts, 0, sizeof(col_digit_counts));
        for (int j = 0; j < 9; j++) {
            row_digit_counts[board[get_index(i,j)]]++;
            col_digit_counts[board[get_index(j,i)]]++;
        }
        if (!legal_counts(row_digit_counts) || !legal_counts(col_digit_counts)) {
            return 0;
        }
    }
    for (int i = 0; i < 9; i++) {
        int box_digit_counts[10];
        memset(box_digit_counts, 0, sizeof(box_digit_counts));
        for (int j = 0; j < 81; j++) {
            if (3*(j/27)+(j%9)/3 == i) box_digit_counts[board[j]]++;
        }
        if (!legal_counts(box_digit_counts)) return 0;
    }
    return 1;
}

int get_empty_position(int* board) {
    for (int i = 0; i < 81; i++) {
        if (board[i] == 0) return i;
    }
    return -1;
}

struct SolveState {
    int board[81];
    bool success;
};

struct SolveState solve(struct SolveState* state) {
    int current_pos = get_empty_position(state->board);
    int board_copy[81];
    memcpy(&board_copy, state->board, sizeof(board_copy));
    if (current_pos == -1) return *state;
    for (int d = 1; d <= 9; d++) {
        (state->board)[current_pos] = d;
        if (legal_board(state->board)) {
            struct SolveState curr_state = {state->board, 0};
            struct SolveState temp = solve(&curr_state);
            if (temp.success) return temp;
        }
    }
    struct SolveState failed_state = {state->board, 1};
    return failed_state;
}

int main() {
    int board[] = {3, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 7, 0, 0, 0, 7, 0, 6, 0, 3, 0, 5, 0, 0, 0, 7, 0, 0, 0, 9, 0, 8, 0, 9, 0, 0, 0, 2, 0, 0, 0, 4, 0, 1, 0, 8, 0, 0, 0, 5, 0, 0, 0, 9, 0, 4, 0, 3, 0, 1, 0, 0, 0, 7, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 8, 0, 0, 6};
    struct SolveState s = {board, 0};
    struct SolveState temp = solve(&s);
    for (int i = 0; i < 81; i++) {
        printf("%d", temp.board[i]);
    }
    return 0;
}
