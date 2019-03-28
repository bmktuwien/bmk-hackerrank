# -*- coding: utf-8 -*-
from __future__ import absolute_import, print_function, unicode_literals, division

cache = set()


def get_sig(c):
    tmp = sorted([c[1], c[2], c[3]])
    return tuple(c[0]), tuple(tmp[0]), tuple(tmp[1]), tuple(tmp[2])


def check_target(c, n):
    return len(c[0]) == n


def solve(c, n):
    candidates = [c]

    q = 0
    while candidates:
        new_candidates = []

        for c in candidates:
            for i in range(4):
                for j in range(4):
                    if c[i] and (not c[j] or c[i][-1] < c[j][-1]):
                        c[j].append(c[i].pop())
                        new_sig = get_sig(c)

                        if check_target(c, n):
                            print(q+1)
                            return

                        if new_sig not in cache:
                            cache.add(new_sig)
                            new_c = [x[:] for x in c]
                            new_candidates.append(new_c)

                        c[i].append(c[j].pop())

        q += 1
        candidates = new_candidates

    print("something went wrong")


def main():
    n = int(raw_input())
    a = map(int, raw_input().rstrip().split())

    c = [[], [], [], []]
    for idx, elem in enumerate(a):
        c[elem-1].insert(0, idx+1)

    solve(c, n)


if __name__ == '__main__':
    main()
