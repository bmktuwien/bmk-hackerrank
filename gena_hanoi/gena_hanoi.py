# -*- coding: utf-8 -*-
from __future__ import absolute_import, print_function, unicode_literals, division

import copy

cache = {}


def get_sig(c):
    return tuple(c[0]), tuple(c[1]), tuple(c[2]), tuple(c[3])


def prune_point(c, N):
    i = 0
    j = N

    while i < len(c[0]) and c[0][i] == j:
        i += 1
        j -= 1

    if i == N:
        return 4
    if i == len(c[0]):
        if len(c[1]) == 1 and c[1][0] == j:
            return 1
        elif len(c[2]) == 1 and c[2][0] == j:
            return 2
        elif len(c[3]) == 1 and c[3][0] == j:
            return 3

    return -1


def solve(c, N):
    candidates = [c]

    q = 0
    while candidates:
        new_candidates = []

        for c in candidates:
            i = prune_point(c, N)

            if i == 4:
                print(q)
                return
            if i > -1:
                c[0].append(c[i].pop())

                new_sig = get_sig(c)

                if new_sig not in cache:
                    cache[new_sig] = q+1
                    new_c = copy.deepcopy(c)
                    new_candidates.append(new_c)

                c[i].append(c[0].pop())

        if not new_candidates:
            for c in candidates:
                for i in range(4):
                    for j in range(4):
                        if c[i] and (not c[j] or c[i][-1] < c[j][-1]):
                            c[j].append(c[i].pop())

                            new_sig = get_sig(c)

                            if new_sig not in cache:
                                cache[new_sig] = q+1
                                new_c = copy.deepcopy(c)
                                new_candidates.append(new_c)

                            c[i].append(c[j].pop())

        q += 1
        candidates = new_candidates

    print("something went wrong")


def main():
    N = int(raw_input())
    a = map(int, raw_input().rstrip().split())

    c = [[], [], [], []]
    for idx, elem in enumerate(a):
        c[elem-1].insert(0, idx+1)

    solve(c, N)


if __name__ == '__main__':
    main()
