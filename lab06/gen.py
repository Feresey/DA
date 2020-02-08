#!/usr/bin/env python

import sys
import random

tests = int(sys.argv[1]) if len(sys.argv) > 1 else 10000

operators = {'+': lambda a, b: a + b,
             '-': lambda a, b: a - b,
             '*': lambda a, b: a * b,
             '^': lambda a, b: a ** b,
             '/': lambda a, b: a // b}

IN = open("input", "w")
OUT = open("output", "w")

for i in range(tests):
    operator = random.choice(list(operators.keys()))
    a = random.randint(0, 2000 if operator == '^' else 10 ** 35)
    b = random.randint(0, 2000 if operator == '^' else 10 ** 35)

    if (operator == '/' and b == 0) or (operator is '-' and a < b) or (operator == '^' and a == b == 0):
        res = "Error"
    else:
        res = operators[operator](a, b)

    print(a, b, operator, sep='\n', file=IN)
    print(res, end='\n', file=OUT)

IN.close()
OUT.close()
