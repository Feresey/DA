#!/usr/bin/python

import random
import sys

if len(sys.argv) == 1:
    print("Usage:\n{} <pair count>(int) <output file>(default stdout)".format(
        sys.argv[0]))
    exit(1)

print("set output array>>> ", end='')
line = [int(i) for i in input().split()]

with (sys.stdout if len(sys.argv) < 3 else open(sys.argv[2], 'w')) as out:
    print(len(line), int(sys.argv[1]), file=out)
    for i in range(int(sys.argv[1])):
        rnd = random.randint(1, len(line)-1)
        print(line[rnd-1], line[random.randint(rnd+1, len(line))-1], file=out)
