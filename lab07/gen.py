#!/usr/bin/python
from sys import exit,argv


def get_res(n, m):
    count = 0
    for i in range(1, n):
        if str(i) < str(n) and i % m == 0:
            count += 1
    return count


def main():
    if len(argv) < 3:
        print("Usage: {} n m".format(argv[0]))
        return 1
    i = int(argv[1])
    j = int(argv[2])
    test = open("./tests/{}.t".format(argv[1]+"_"+argv[2]), 'w')
    ans = open("./tests/{}.a".format(argv[1]+"_"+argv[2]), 'w')
    print(i, j, file=test)
    print(get_res(i, j), file=ans)
    test.close()
    ans.close()
    return 0

if __name__ == "__main__":
    exit(main())
