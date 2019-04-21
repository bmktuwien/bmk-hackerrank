#!/bin/python

from __future__ import print_function

import os
import sys
import math

from collections import *

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


def distance_pow2(biker, bike):
    return (biker[0]-bike[0])**2 + (biker[1]-bike[1])**2


def bikeRacers(bikers, bikes, k):
    candidates = []

    for i in range(len(bikers)):
        for j in range(len(bikes)):
            candidates.append((distance_pow2(bikers[i], bikes[j]), i, j))

    candidates = sorted(candidates)

    U = set()
    V = set()
    E = defaultdict(set)

    for i in range(len(candidates)):
        d, biker, bike = candidates[i]
        U.add(biker)
        V.add(-bike)
        E[biker].add(-bike)

        if i >= k-1:
            max_matching = hopcraft_karp(U, V, E)

            if max_matching >= k:
                print(d)
                return


if __name__ == '__main__':
    nmk = raw_input().split()

    n = int(nmk[0])
    m = int(nmk[1])
    k = int(nmk[2])

    bikers = []

    for _ in xrange(n):
        bikers.append(map(int, raw_input().rstrip().split()))

    bikes = []

    try:
        for _ in xrange(n):
            bikes.append(map(int, raw_input().rstrip().split()))
    except Exception:
        pass

    bikeRacers(bikers, bikes, k)


