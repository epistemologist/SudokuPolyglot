ROW = [[i for i in range(81) if i//9 == j] for j in range(9)]
COL = [[i for i in range(81) if i % 9 == j] for j in range(9)]
BOX = [[i for i in range(81) if 3*(i//27) + (i%9)//3 == j] for j in range(9)]
DIGITS = range(1,10)

pair = lambda x,y: tuple(sorted([x,y]))

equality_pairs = set()

code = ""

for i, row in enumerate(ROW):
    code += f"# Row {i+1}\n"
    terms = []
    for a in range(9):
        for b in range(a):
            equality_pairs.add(pair(row[a],row[b]))
            terms.append(f"p.n{row[a]+1} <> p.n{row[b]+1}")
    terms.append('')
    code += " and ".join(terms) + "\n"

for i, col in enumerate(COL):
    code += f"# Col {i+1}\n"
    terms = []
    for a in range(9):
        for b in range(a):
            if pair(col[a],col[b]) not in equality_pairs:
                equality_pairs.add(pair(col[a],col[b]))
                terms.append(f"p.n{col[a]+1} <> p.n{col[b]+1}")
    terms.append('')
    code += " and ".join(terms) + "\n"

for i, box in enumerate(BOX):
    code += f"# Box {i+1}\n"
    terms = []
    for a in range(9):
        for b in range(a):
            if pair(box[a],box[b]) not in equality_pairs:
                equality_pairs.add(pair(box[a], box[b]))
                terms.append(f"p.n{box[a]+1} <> p.n{box[b]+1}")
    terms.append('')
    code += " and ".join(terms) + "\n"


print("\n" + code[:-6])
