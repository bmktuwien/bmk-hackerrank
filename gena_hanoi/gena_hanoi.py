# -*- coding: utf-8 -*-
from __future__ import absolute_import, print_function, unicode_literals, division

import copy

cache = {}
N = 0
target_sig = ''


def get_sig(c):
    sig = ''
    for r in c:
        sig += ''.join(map(str, r)).zfill(N)

    return sig


def solve(c):
    candidates = [c]

    while candidates:
        new_candidates = []

        for c, q in candidates:
            for i in range(4):
                for j in range(4):
                    if c[i] and (not c[j] or c[i][-1] < c[j][-1]):
                        new_c = copy.deepcopy(c)

                        new_c[j].append(new_c[i].pop())
                        new_q = q + 1

                        new_sig = get_sig(new_c)

                        if new_sig in cache:
                            cached_q = cache[new_sig]
                            if new_q < cached_q:
                                print(new_sig, new_q)
                                cache[new_sig] = new_q
                                new_candidates.append((new_c, new_q))
                        else:
                            cache[new_sig] = new_q
                            new_candidates.append((new_c, new_q))

        candidates = new_candidates


def main():
    global N
    global target_sig

    N = int(raw_input())
    a = map(int, raw_input().rstrip().split())

    c = [[], [], [], []]
    for idx, elem in enumerate(a):
        c[elem-1].insert(0, idx+1)

    target_sig = ''.join(map(str, reversed(range(1, N+1)))) + '0'*N + '0'*N + '0'*N

    solve((c, 0))
    print(cache[target_sig])


if __name__ == '__main__':
    main()
