#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std; 

vector<vector<int>> gen_groups() {
    vector<vector<int>> out;
    // Generate indices of rows
    for (int i = 0; i < 9; i++) {
        vector<int> temp;
        for (int j = 0; j < 81; j++) {
            if (j / 9 == i) temp.push_back(j);
        }
        out.push_back(temp);
    }
    // Generate indices of cols
    for (int i = 0; i < 9; i++) {
        vector<int> temp;
        for (int j = 0; j < 81; j++) {
            if (j % 9 == i) temp.push_back(j);
        }
        out.push_back(temp);
    }
    // Generate indices of boxs
    for (int i = 0; i < 9; i++) {
        vector<int> temp;
        for (int j = 0; j < 81; j++) {
            if (3 * (j/27) + (j%9)/3 == i) temp.push_back(j);
        }
        out.push_back(temp);
    }
    return out;
}

vector<vector<int>> GROUPS = gen_groups();

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
        print_board(solve(get_board(line)));
    }
}
