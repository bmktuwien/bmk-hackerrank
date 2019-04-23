# -*- coding: utf-8 -*-

#!/bin/python

from collections import *
from fractions import *


def trial_division(n):
    a = set()
    while n % 2 == 0:
        a.add(2)
        n /= 2

    f = 3

    while f * f <= n:
        if n % f == 0:
            a.add(f)
            n /= f
        else:
            f += 2

    if n != 1:
        a.add(n)

    return a


def gen_primes():
    D = {}

    q = 2

    while True:
        if q not in D:
            yield q
            D[q * q] = [q]
        else:
            for p in D[q]:
                D.setdefault(p + q, []).append(p)
            del D[q]

        q += 1


def computer_game(n, a, b):
    count = 0
    for i in a:
        factors = trial_division(a[0])
        print(factors)

    print(count)


if __name__ == '__main__':
    n = int(raw_input())

    a = map(int, raw_input().rstrip().split())

    b = map(int, raw_input().rstrip().split())

    computer_game(n, a, b)

