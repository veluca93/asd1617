#!/usr/bin/env python2

import sys
import random

if len(sys.argv) < 2:
    print "Usage: %s num [spread [seed]]" % sys.argv[0]
    exit(1)

n = int(sys.argv[1])

if len(sys.argv) >= 3:
    spread = int(sys.argv[2])
else:
    spread = 1000

if len(sys.argv) >= 4:
    random.seed(sys.argv[3])

print n
for i in range(n):
    print random.randint(-spread, spread),
