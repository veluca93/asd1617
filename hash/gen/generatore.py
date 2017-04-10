#!/usr/bin/env python2

import math
import sys
import random

if len(sys.argv) < 5:
    print "Usage: %s spread n_find n_insert n_delete [seed]" % sys.argv[0]
    exit(1)

spread = int(sys.argv[1])
find = int(sys.argv[2])
insert = int(sys.argv[3])
delete = int(sys.argv[4])

if len(sys.argv) > 5:
    random.seed(sys.argv[5])

print find+insert+delete

ops = ['f' for _ in range(find)] + ['i' for _ in range(insert)] + \
    ['d' for _ in range(delete)]

random.shuffle(ops)
for op in ops:
    print op, random.randint(-spread, spread)
