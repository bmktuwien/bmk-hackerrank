# -*- coding: utf-8 -*-
from __future__ import absolute_import, print_function, unicode_literals, division

rods = [[], [], [], []]
cache = {}
N = 0
target_sig = ''
marked = {}


def get_sig():
    sig = ''
    for r in rods:
        sig += ''.join(map(str, r)).zfill(N)

    return sig


def solve():
    sig = get_sig()
    marked[sig] = True
    print(target_sig)

    if sig == target_sig:
        print("fuck!!!")
        return 0

    candidates = []
    print(sig)
    print(rods)

    for i in range(4):
        for j in range(4):
            if rods[i] and (not rods[j] or rods[i][-1] < rods[j][-1]):
                rods[j].append(rods[i].pop())

                new_sig = get_sig()
                
                if new_sig in cache:
                    print("cache hit")
                    candidates.append(cache[new_sig] + 1)
                else:
                    if new_sig not in marked:
                        q = solve()
                        if q >= 0:
                            candidates.append(q+1)
                    else:
                        print("no recursion")

                rods[i].append(rods[j].pop())

    if candidates:
        cache[sig] = min(candidates)
        return cache[sig]
    else:
        return -1


def main():
    global N
    global target_sig

    N = int(raw_input())
    a = map(int, raw_input().rstrip().split())

    for idx, elem in enumerate(a):
        rods[elem-1].insert(0, idx+1)

    target_sig = ''.join(map(str, reversed(range(1, N+1)))) + '0'*N + '0'*N + '0'*N

    result = solve()

    print(rods)
    print(result)


if __name__ == '__main__':
    main()
