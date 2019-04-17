# -*- coding: utf-8 -*-

from collections import *


def problem_solving(n, k, v):
    a = []

    for i in range(n):
        flag = False
        for j, x in enumerate(a):
            if abs(v[i]-v[x]) >= k:
                flag = True
                a[j] = i
                break

        if not flag:
            a.append(i)

    print(a)
    print(len(a))

if __name__ == '__main__':
    t = int(raw_input())

    for _ in range(t):
        nk = raw_input().split()

        n = int(nk[0])

        k = int(nk[1])

        v = map(int, raw_input().rstrip().split())

        problem_solving(n, k, v)
