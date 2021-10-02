board=(0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0)

legal_board_() {
    # Function that checks whether $board contains a legal sudoku board

    # Check rows and columns
	for ((i=0;i<9;i++))
	do
		curr_row=1
		curr_col=1
		for ((j=0;j<9;j++))
		do
            curr_row_elem=$(( 1<<${board[9*i+j]} ))
			if (( ($curr_row_elem & $curr_row) > 1  ))
			then
				false; return
			else
				((curr_row|=curr_row_elem))
			fi
			curr_col_elem=$(( 1<<${board[9*j+i]} ))
			if (( ($curr_col_elem & $curr_col) > 1 ))
			then
				false; return
			else
				((curr_col|=curr_col_elem))
			fi
		done
	done
	# Check boxes
	for ((i=0;i<9;i++))
	do
		curr_box=1
		for ((j=0;j<81;j++))
		do
			if ((3*(j/27)+(j%9)/3==i))
			then
				curr_box_elem=$(( 1<<${board[j]} ))
				if (( ($curr_box_elem & $curr_box) > 1 ))
				then
					false; return
				else
					((curr_box|=curr_box_elem))
				fi
			fi
		done
	done
	true; return
}

is_solved_() {
    # Checks whether or not $board is solved
	for ((i=0;i<81;i++))
	do
		if [[ ${board[i]} -eq 0 ]]
		then
			false; return
		fi
	done
	true; return
}

legal_board() {
    board=("${board_to_solve[@]}")
    if legal_board_; then
        true; return
    else
        false; return
    fi
}

is_not_solved() {
    # Returns whether or not $board_to_solve is not solved
    board=("${board_to_solve[@]}")
    if is_solved_; then
        false; return
    else
        true; return
    fi
}

solve() {
    iter=0
    current_pos=0
    board_copy=("${board_to_solve[@]}")
    while is_not_solved
    do
        # echo $puzzles_done, ${board_to_solve[*]}
        flag=1
        if (( ${board_to_solve[current_pos]} > 0 && ${board_to_solve[current_pos]} < 10 ))
        then
            if legal_board; then
                flag=0
                ((current_pos++))
            fi
        fi

        if (( $flag == 1 )); then
            (( board_to_solve[$current_pos]++ ))
        fi

        if [[ ${board_to_solve[$current_pos]} -gt 9 ]]; then
            board_to_solve[$current_pos]=0
            ((current_pos--))
            while [[ ${board_copy[current_pos]} -ne 0 ]]
            do
                ((current_pos--))
            done
            (( board_to_solve[$current_pos]++ ))
        fi
        if (( $iter % 1 == 0 )); then
            echo $puzzles_done, $iter, ${board_to_solve[*]}
        fi
        (( iter++ ))
    done
}

line="000900002050123400030000160908000000070000090000000205091000050007439020400007000"
board_to_solve=($(echo $line | fold -w1))
solve
#
#main() {
#    puzzles_done=0
#   while IFS= read -r line; do
#        board_to_solve=($(echo $line | fold -w1))
#        solve
#        printf "%d%d%d%d%d%d%d%d%d\n" ${board_to_solve[*]}
#        printf '\n'
#        ((puzzles_done++))
#    done < "../sudoku_puzzles"
#}
#
#main
