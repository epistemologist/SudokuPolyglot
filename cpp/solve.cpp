#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std; 

vector<vector<int>> GROUPS = {{0, 1, 2, 3, 4, 5, 6, 7, 8}, {9, 10, 11, 12, 13, 14, 15, 16, 17}, {18, 19, 20, 21, 22, 23, 24, 25, 26}, {27, 28, 29, 30, 31, 32, 33, 34, 35}, {36, 37, 38, 39, 40, 41, 42, 43, 44}, {45, 46, 47, 48, 49, 50, 51, 52, 53}, {54, 55, 56, 57, 58, 59, 60, 61, 62}, {63, 64, 65, 66, 67, 68, 69, 70, 71}, {72, 73, 74, 75, 76, 77, 78, 79, 80}, {0, 9, 18, 27, 36, 45, 54, 63, 72}, {1, 10, 19, 28, 37, 46, 55, 64, 73}, {2, 11, 20, 29, 38, 47, 56, 65, 74}, {3, 12, 21, 30, 39, 48, 57, 66, 75}, {4, 13, 22, 31, 40, 49, 58, 67, 76}, {5, 14, 23, 32, 41, 50, 59, 68, 77}, {6, 15, 24, 33, 42, 51, 60, 69, 78}, {7, 16, 25, 34, 43, 52, 61, 70, 79}, {8, 17, 26, 35, 44, 53, 62, 71, 80}, {0, 1, 2, 9, 10, 11, 18, 19, 20}, {3, 4, 5, 12, 13, 14, 21, 22, 23}, {6, 7, 8, 15, 16, 17, 24, 25, 26}, {27, 28, 29, 36, 37, 38, 45, 46, 47}, {30, 31, 32, 39, 40, 41, 48, 49, 50}, {33, 34, 35, 42, 43, 44, 51, 52, 53}, {54, 55, 56, 63, 64, 65, 72, 73, 74}, {57, 58, 59, 66, 67, 68, 75, 76, 77}, {60, 61, 62, 69, 70, 71, 78, 79, 80}};

bool legal_board(vector<int> board) {
    for (vector<int> g: GROUPS) {
        vector<int> digits(10, 0);
        for (int i: g) {
            digits[board[i]]++;
        }
        if (*max_element(digits.begin() + 1, digits.end()) > 1) return false;
    }
    return true;
}

bool is_solved(vector<int> board) {
    return find(board.begin(), board.end(), 0) == board.end();
}

vector<int> get_board(string board) {
    vector<int> out;
    for (char i: board) {
        out.push_back(i - '0');
    }
    return out;
}

void print_board(vector<int> board) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) cout << board[9*i+j];
        cout << endl;
    }
    cout << endl;
}

vector<int> solve(vector<int> board) {
    if (is_solved(board)) return board;
    vector<int> board_copy(board.begin(), board.end());
    int current_pos = find(board.begin(), board.end(), 0) - board.begin();
    for (int digit = 1; digit <= 9; digit++) {
        board[current_pos] = digit;
        if (legal_board(board)) {
            auto temp = solve(board);
            if (temp.size() > 0) return temp;
        }
        board.assign(board_copy.begin(), board_copy.end());
    }
    return {};
}


int main() {
    ifstream file;
    string line;
    file.open("../sudoku_puzzles");
    while (getline(file, line)) {
        cout << line << endl;
        print_board(solve(get_board(line)));
    }
}
