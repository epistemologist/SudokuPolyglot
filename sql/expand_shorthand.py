#!/usr/bin/python3

import subprocess

p = subprocess.Popen("python3 ./gen_board_logic.py".split(), stdout=subprocess.PIPE)
logic = p.communicate()[0]

f = open("gen_db.sql", "r").read()

f = f.replace("n1,...,n81", ",".join(map(lambda x: f"n{x}", range(1,82))))
f = f.replace("logic", logic.decode())
print(f)
