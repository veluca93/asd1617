#!/usr/bin/env python2

import sys
import random

def build_tree(root, children, labels, start, end):
    left, right = -1, -1
    leftsz = random.randint(0, end-start)
    if leftsz != 0:
        left = labels[start]
        build_tree(start, children, labels, start+1, start+leftsz)
    if leftsz + start != end:
        right = labels[start+leftsz]
        build_tree(start+leftsz, children, labels, start+leftsz+1, end)
    children[labels[root]] = (left, right)

if len(sys.argv) < 2:
    print "Usage: %s num [seed]" % sys.argv[0]
    exit(1)

n = int(sys.argv[1])
if len(sys.argv) >= 3:
    random.seed(sys.argv[2])

labels = list(range(n))
random.shuffle(labels)

print n, labels[0]

avail = range(1, n)
random.shuffle(avail)

children = [(0, 0) for _ in range(n)]

build_tree(0, children, labels, 1, n)

sz = len(str(n-1))
fmt = "%" + str(sz) + "d %" + str(sz+1) + "d %" + str(sz+1) + "d"
for i in range(n):
    print fmt % (i, children[i][0], children[i][1])
