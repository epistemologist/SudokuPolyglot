<?php

$ROW = $COL = $BOX =  array();
for ($i=0; $i<9; $i++) {
    $row = $col = $box = array();
    for ($j=0; $j<81; $j++) {
        if ( intdiv($j,9) == $i ) { $row[] = $j; }
        if ( $j % 9 == $i ) { $col[] = $j; }
        if ( 3*intdiv($j,27) + intdiv($j%9,3) == $i ) { $box[] = $j; }
    }
    $ROW[] = $row;
    $COL[] = $col;
    $BOX[] = $box;
}

$GROUPS = array_merge($ROW, $COL, $BOX);
$group = [1,2,3,4,5,6,7,8,9];

function legal_group($group) {
    return (int) max(array_count_values(array_filter($group, fn($x) => $x > 0))) < 2;
}

function legal_board($board) {
    global $GROUPS;
    $board_groups = array_map(fn($group) => array_map(fn($x) => $board[$x], $group), $GROUPS);
    foreach (array_map("legal_group", $board_groups) as $i) {
        if (!$i) return false;
    }
    return true;
}

function is_solved($board) {
    foreach ($board as $i) {
        if ($i == 0) return false;
    }
    return true;
}

function solve($board) { 
    if (is_solved($board)) {
        return $board;
    }
    $board_copy = $board;
    $current_pos = 0;
    while ($board[$current_pos] != 0) {
        $current_pos++;
    }
    foreach (range(1,9) as $digit) {
        $board[$current_pos] = $digit;
        if (legal_board($board)) {
            $temp = solve($board);
            if ($temp) { return $temp;  }
        }
        $board = $board_copy;
    }
    return False;
}

function print_board($board) {
    for ($i=0; $i<81; $i++) {
        echo $board[$i];
        if ($i%9==8) echo "\n";
    }
}


$sudoku_puzzles = fopen("../sudoku_puzzles", "r");

$puzzle = [0, 0, 3, 0, 2, 0, 6, 0, 0, 9, 0, 0, 3, 0, 5, 0, 0, 1, 0, 0, 1, 8, 0, 6, 4, 0, 0, 0, 0, 8, 1, 0, 2, 9, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 8, 0, 0, 6, 7, 0, 8, 2, 0, 0, 0, 0, 2, 6, 0, 9, 5, 0, 0, 8, 0, 0, 2, 0, 3, 0, 0, 9, 0, 0, 5, 0, 1, 0, 3, 0, 0];


while (!feof($sudoku_puzzles)) {
    $line = fgets($sudoku_puzzles);
    $puzzle = array_map(intval, str_split(trim($line)));
    print_board(solve($puzzle));
    echo "\n";
} 
?>



