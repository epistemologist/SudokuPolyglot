puzzles = open("../sudoku_puzzles", "r").readlines()
elems = [f"n{i}" for i in range(1,82)]
schema = "create table puzzle(\n"+ "\n".join([f"\t{elem} int, " for elem in elems])[:-2] + "\n);"

print(schema)
for puzzle in puzzles:
    puzzle = puzzle.strip()

    print("insert into puzzle (%s) values %s;" % (
        ",".join(elems),
        "(" + ",".join(map(str, puzzle)) + ")"
    ))
