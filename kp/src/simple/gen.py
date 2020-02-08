#!/usr/bin/python

import sys
from random import randint as ri

out = open(sys.argv[2],'w')

for i in range(int(sys.argv[1])):
    print(*sorted([ri(1,2**27) for _ in range(30000)]), file=out)

