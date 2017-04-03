#!/usr/bin/env python2

import math
import sys
import random

if len(sys.argv) < 7:
    print "Usage: %s num spread n_find n_insert n_delete n_range [seed]" % sys.argv[0]
    exit(1)

n = int(sys.argv[1])
spread = int(sys.argv[2])
find = int(sys.argv[3])
insert = int(sys.argv[4])
delete = int(sys.argv[5])
rng = int(sys.argv[6])

if len(sys.argv) > 7:
    random.seed(sys.argv[7])

if spread < n:
    spread = n

all_numbers = list(range(-spread, spread+1))

random.shuffle(all_numbers)

print n, find+insert+delete+rng
print '\n'.join(map(str, sorted(all_numbers[:n])))

ops = ['f' for _ in range(find)] + ['i' for _ in range(insert)] + \
    ['d' for _ in range(delete)] + ['r' for _ in range(rng)]

random.shuffle(ops)
for op in ops:
    if op != 'r':
        print op, random.randint(-spread, spread)
    else:
        a, b = random.randint(-spread, spread), random.randint(-spread, spread)
        if a > b:
            a, b = b, a
        print op, a, b
