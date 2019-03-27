# -*- coding: utf-8 -*-
from __future__ import absolute_import, print_function, unicode_literals, division

import copy

cache = {}
N = 0
target_sig = ''


def get_sig(c):
    return tuple(c[0]), tuple(c[1]), tuple(c[2]), tuple(c[3])


def solve(c):
    candidates = [c]

    while candidates:
        new_candidates = []

        for c, q in candidates:
            for i in range(4):
                for j in range(4):
                    if c[i] and (not c[j] or c[i][-1] < c[j][-1]):
                        c[j].append(c[i].pop())
                        new_q = q + 1

                        new_sig = get_sig(c)

                        if new_sig == target_sig:
                            print(new_q)
                            return

                        if new_sig not in cache:
                            cache[new_sig] = new_q
                            new_c = copy.deepcopy(c)
                            new_candidates.append((new_c, new_q))

                        c[i].append(c[j].pop())

        print(len(new_candidates))
        candidates = new_candidates

    print("something went wrong")


def main():
    global N
    global target_sig

    N = int(raw_input())
    a = map(int, raw_input().rstrip().split())

    c = [[], [], [], []]
    for idx, elem in enumerate(a):
        c[elem-1].insert(0, idx+1)

    target_sig = get_sig([list(reversed(range(1, N+1))), [], [], []])

    solve((c, 0))


if __name__ == '__main__':
    main()
