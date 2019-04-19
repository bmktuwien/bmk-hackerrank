# -*- coding: utf-8 -*-

from collections import *

INF = float('inf')


def bfs(U, V, E, pair_u, pair_v, dist):
    Q = deque()

    for u in U:
        if pair_u[u] is None:
            dist[u] = 0
            Q.append(u)
        else:
            dist[u] = None

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
    dist = {}

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


def problem_solving(n, k, v):
    G = defaultdict(lambda: ([], [])) #out,in

    for i in range(n):
        for j in range(i):
            if abs(v[i]-v[j]) >= k:
                G[j][0].append(i)
                G[i][1].append(j)

    print(G)

    v_out = set()
    v_in = set()
    for i in range(n):
        outgoing, ingoing = G[i]

        if (len(outgoing) - len(ingoing)) > 0:
            v_out.add(i)
        elif (len(ingoing) - len(outgoing)) > 0:
            v_in.add(i)

    edges = defaultdict(list)
    for v in v_out:
        for neighbor in G[v][0]:
            if neighbor in v_in:
                edges[v].append(neighbor)

    print(v_out)
    print(v_in)
    print(edges)

    print(hopcraft_karp(v_out, v_in, edges))

if __name__ == '__main__':
    t = int(raw_input())

    for _ in range(t):
        nk = raw_input().split()

        n = int(nk[0])

        k = int(nk[1])

        v = map(int, raw_input().rstrip().split())

        problem_solving(n, k, v)
