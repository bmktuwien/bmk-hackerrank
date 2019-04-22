# -*- coding: utf-8 -*-

#!/bin/python

from collections import *
from fractions import *


def is_prime(n):
    if n == 1:
        return False

    i = 2
    while i*i <= n:
        if n % i == 0:
            return False
        i += 1

    return True


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


def gen_edges(n, a):
    E = defaultdict(set)
    t = set(range(n))

    count = 0
    flag = False
    for p in gen_primes():
        new_t = set()
        for i in t:
            if a[i] % p == 0:
                E[p].add(i)
            else:
                new_t.add(i)

            t = new_t

        if not t:
            break

        count += 1
        if count >= 100 and not flag:
            flag = True
            new_t = set()

            for i in t:
                if is_prime(a[i]):
                    E[a[i]].add(i)
                else:
                    new_t.add(i)
            t = new_t


    return E


def computer_game(n, a, b):
    E = gen_edges(n, a)
    print('done')


if __name__ == '__main__':
    n = int(raw_input())

    a = map(int, raw_input().rstrip().split())

    b = map(int, raw_input().rstrip().split())

    computer_game(n, a, b)

