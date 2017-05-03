#!/usr/bin/env python2

from limiti import *

from sys import argv, exit, stderr
import os

def usage():
    print >> stderr, "Usage: %s file_input.txt" % \
        os.path.basename(argv[0])
    exit(1)

def run(f):
    assert(len(f) >= 2)
    prima = [int(x) for x in f[0].split()]
    assert(len(prima) == 2)
    N, M = prima
    assert(1 <= N and N <= MAXN)
    assert(1 <= M and M <= MAXM)
    #~ seconda = [int(x) for x in f[1].split()]
    #~ assert(len(seconda) == 2)
    #~ s, t = seconda
    #~ assert(0 <= s and s <= N-1)
    #~ assert(0 <= t and t <= N-1)
    for i in xrange(M):
        riga = [int(x) for x in f[i+1].split()]
        assert(len(riga) == 3)
        a, b, c = riga
        assert(0 <= a and a <= MAXN-1)
        assert(0 <= b and b <= MAXN-1)
        assert(1 <= c and c <= MAXP)
    return 0 # Input corretto

if __name__ == "__main__":
    if len(argv) < 2:
        usage()

    f = open(argv[1]).readlines()
    exit(run(f))


