# -*- coding: utf-8 -*-

from __future__ import absolute_import
from __future__ import print_function
from __future__ import unicode_literals
from __future__ import division
#!/bin/python

from __future__ import print_function

import os
import sys

from collections import *
from fractions import *

INF = float('inf')


def bfs(U, V, E, pair_u, pair_v, dist):
    Q = deque()

    for u in U:
        if pair_u[u] is None:
            dist[u] = 0
            Q.append(u)
        else:
            dist[u] = INF

    dist[None] = INF

    while Q:
        u = Q.popleft()
        if dist[u] < dist[None]:
            for v in E[u]:
                if dist[pair_v[v]] == INF:
                    dist[pair_v[v]] = dist[u] + 1
                    Q.append(pair_v[v])

    return dist[None] != INF


def dfs(u, E, pair_u, pair_v, dist):
    if u is not None:
        for v in E[u]:
            if dist[pair_v[v]] == dist[u] + 1:
                if dfs(pair_v[v], E, pair_u, pair_v, dist):
                    pair_v[v] = u
                    pair_u[u] = v
                    return True

        dist[u] = INF
        return False
    else:
        return True


def hopcraft_karp(U, V, E):
    pair_u = {}
    pair_v = {}
    dist = defaultdict(lambda: INF)

    for u in U:
        pair_u[u] = None
    for v in V:
        pair_v[v] = None

    matching = 0
    while bfs(U, V, E, pair_u, pair_v, dist):
        for u in U:
            if pair_u[u] is None:
                if dfs(u, E, pair_u, pair_v, dist):

                    matching += 1
    return matching


def computer_game(n, a, b):
    U = range(n)
    V = range(n)
    E = defaultdict(set)

    for i, p in enumerate(a):
        for j, q in enumerate(b):
            if gcd(p, q) != 1:
                E[i].add(j)

    result = hopcraft_karp(U, V, E)
    print(result)


if __name__ == '__main__':
    n = int(raw_input())

    a = map(int, raw_input().rstrip().split())

    b = map(int, raw_input().rstrip().split())

    computer_game(n, a, b)

