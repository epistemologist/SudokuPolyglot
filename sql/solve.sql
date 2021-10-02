create table digits(n int);
insert into digits (n) values (1),(2),(3),(4),(5),(6),(7),(8),(9);

create table puzzles(puzzle string);
insert into puzzles values (trim(readfile("../sudoku_puzzles"), char(81)));
