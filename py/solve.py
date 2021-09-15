from typing import List, Optional
from time import time

ROW = [[i for i in range(81) if i//9 == j] for j in range(9)]
COL = [[i for i in range(81) if i % 9 == j] for j in range(9)]
BOX = [[i for i in range(81) if 3*(i//27) + (i%9)//3 == j] for j in range(9)]
DIGITS = range(1,10)

legal_group = lambda group: all([group.count(d) < 2 for d in DIGITS])
is_solved = lambda board: board.count(0) == 0

def legal_board(board: List[int]) -> bool:
    rows = [[board[j] for j in i] for i in ROW]
    cols = [[board[j] for j in i] for i in COL]
    boxs = [[board[j] for j in i] for i in BOX]
    return all(map(legal_group, rows + cols + boxs))

def repr_board(board: List[int]) -> str:
    return "\n".join(["".join(map(str,board[i:i+9])) for i in range(0,81,9)])

def solve(board: List[int]) -> Optional[List[int]]:
    if is_solved(board): return board
    board_copy = board[:]
    current_pos = board.index(0)
    for digit in DIGITS:
        board[current_pos] = digit
        if legal_board(board):
            temp = solve(board)
            if temp: return temp
        board = board_copy[:]
    return None

puzzles = [[int(digit) for digit in puzzle.strip()] for puzzle in open("../sudoku_puzzles", "r").readlines()]
for puzzle in puzzles:
    print(repr_board(solve(puzzle)) + "\n")
