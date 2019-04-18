# -*- coding: utf-8 -*-

from collections import *


def problem_solving(n, k, v):
    g = defaultdict(lambda: ([], [])) #out,in

    for i in range(n):
        for j in range(i):
            if abs(v[i]-v[j]) >= k:
                g[j][0].append(i)
                g[i][1].append(j)

    v_out = []
    v_in = []
    for i in range(n):
        outgoing, ingoing = g[i]

        if (len(outgoing) - len(ingoing)) > 0:
            v_out.append(i)
        elif (len(ingoing) - len(outgoing)) > 0:
            v_in.append(i)

    print(v_out)
    print(v_in)


if __name__ == '__main__':
    t = int(raw_input())

    for _ in range(t):
        nk = raw_input().split()

        n = int(nk[0])

        k = int(nk[1])

        v = map(int, raw_input().rstrip().split())

        problem_solving(n, k, v)
