# -*- coding: utf-8 -*-

#!/bin/python

from collections import *
from fractions import *


def trial_division(n):
    a = set()

    while n % 2 == 0:
        a.add(2)
        n /= 2

    f = 3

    while f * f <= n:
        if n % f == 0:
            a.add(f)
            n /= f
        else:
            f += 2

    if n != 1:
        a.add(n)

    return a


def gen_primes():
    D = {}

    q = 2

    while True:
        if q not in D:
            yield q
            D[q * q] = [q]
        else:
            for p in D[q]:
                D.setdefault(p + q, []).append(p)
            del D[q]

        q += 1


def bfs(graph, saturated_edges, level, s, t):  # C is the capacity matrix
    queue = deque()

    queue.append(s)

    level.clear()
    level[s] = 1

    while queue:
        u = queue.popleft()

        for v in graph[u]:
            if level[v] == 0 and ((u,v) not in saturated_edges):
                level[v] = level[u] + 1
                queue.append(v)

    return level[t] > 0


def dfs(graph, saturated_edges, level, u, s, t):
    if u == t:
        return 1

    for v in graph[u]:
        if (level[v] == level[u] + 1) and ((u,v) not in saturated_edges):
            f = dfs(graph, saturated_edges, level, v, s, t)
            if f > 0:
                saturated_edges.add((u,v))
                saturated_edges.discard((v,u))
                return f

    return 0


def max_flow(graph, saturated_edges, s, t):
    level = defaultdict(lambda: 0)

    flow = 0
    while bfs(graph, saturated_edges, level, s, t):
        f = dfs(graph, saturated_edges, level, s, s, t)

        while f > 0:
            flow += f
            f = dfs(graph, saturated_edges, level, s, s, t)

    return flow


def computer_game(n, A, B):

    start_node = -1
    end_node = -2

    graph = defaultdict(set)
    saturated_edges = set()
    prime_nodes_map = {}

    a_node_counter = 0
    p_node_counter = 100000
    for value in A:
        graph[start_node].add(a_node_counter)
        graph[a_node_counter].add(start_node)
        saturated_edges.add((a_node_counter, start_node))

        factors = trial_division(value)
        for p in factors:
            if p not in prime_nodes_map:
                prime_nodes_map[p] = p_node_counter
                p_node_counter += 1

            p_node = prime_nodes_map[p]
            graph[a_node_counter].add(p_node)
            graph[p_node].add(a_node_counter)
            saturated_edges.add((p_node, a_node_counter))

        a_node_counter += 1

    b_node_counter = 300000
    for value in B:
        graph[b_node_counter].add(end_node)
        graph[end_node].add(b_node_counter)
        saturated_edges.add((end_node, b_node_counter))

        factors = trial_division(value)
        for p in factors:
            if p not in prime_nodes_map:
                prime_nodes_map[p] = p_node_counter
                p_node_counter += 1

            p_node = prime_nodes_map[p]
            graph[p_node].add(b_node_counter)
            graph[b_node_counter].add(p_node)
            saturated_edges.add((b_node_counter, p_node))

        b_node_counter += 1

    result = max_flow(graph, saturated_edges, start_node, end_node)
    print(result)


if __name__ == '__main__':
    n = int(raw_input())

    a = map(int, raw_input().rstrip().split())

    b = map(int, raw_input().rstrip().split())

    computer_game(n, a, b)

