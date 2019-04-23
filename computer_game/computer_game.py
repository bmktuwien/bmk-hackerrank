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


def bfs(graph, saturated_edges, s, t, parent):
    visited = set()
    queue = deque()

    queue.append(s)
    visited.add(s)

    while queue:
        u = queue.popleft()

        for v in graph[u]:
            if (v not in visited) and ((u,v) not in saturated_edges):
                queue.append(v)
                visited.add(v)
                parent[v] = u

    return t in visited


def ford_fulkerson(graph, source, sink):
    saturated_edges = set()
    parent = {}

    max_flow = 0

    while bfs(graph, saturated_edges, source, sink, parent):
        max_flow += 1

        v = sink
        while v != source:
            u = parent[v]
            saturated_edges.add((u, v))
            saturated_edges.discard((v, u))
            v = parent[v]

    return max_flow


def computer_game(n, A, B):

    start_node = -1
    end_node = -2

    graph = defaultdict(set)
    prime_nodes_map = {}

    a_node_counter = 0
    p_node_counter = 100000
    for value in A:
        graph[start_node].add(a_node_counter)

        factors = trial_division(value)
        for p in factors:
            if p not in prime_nodes_map:
                prime_nodes_map[p] = p_node_counter
                p_node_counter += 1

            graph[a_node_counter].add(prime_nodes_map[p])

        a_node_counter += 1

    b_node_counter = 300000
    for value in B:
        graph[b_node_counter].add(end_node)

        factors = trial_division(value)
        for p in factors:
            if p not in prime_nodes_map:
                prime_nodes_map[p] = p_node_counter
                p_node_counter += 1

            graph[prime_nodes_map[p]].add(b_node_counter)

        b_node_counter += 1

    print(graph)
    result = ford_fulkerson(graph, start_node, end_node)
    print(result)


if __name__ == '__main__':
    n = int(raw_input())

    a = map(int, raw_input().rstrip().split())

    b = map(int, raw_input().rstrip().split())

    computer_game(n, a, b)

