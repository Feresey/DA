#!/usr/bin/env python
# -*- coding: utf-8 -*-

from random import randint as ri, choice
import sys
from os import urandom as ur
import string

def buildblock(size):
    return ''.join(choice(string.ascii_letters + string.digits) for _ in range(size))


def main():
    if len(sys.argv) < 2:
        print('usage: {} <test count>'.format(sys.argv[0]))
        return 1
    for i in range(int(sys.argv[1])):
        print(ri(0,31),'.',ri(0,13),'.',ri(0,3000),'\t',buildblock(60),sep='')

if __name__ == "__main__":
    sys.exit(main())
