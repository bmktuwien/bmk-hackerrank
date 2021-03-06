# -*- coding: utf-8 -*-

#!/bin/python

from collections import *


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


# precompute prime numbers smaller than sqrt(10**9)
prime_gen = gen_primes()
primes = [next(prime_gen) for _ in xrange(3500)]


# enhanced trial division method using precomputed prime numbers
def trial_division(n):
    a = set()

    while n % 2 == 0:
        a.add(2)
        n /= 2

    i = 1
    f = primes[i]

    while f * f <= n:
        if n % f == 0:
            a.add(f)
            n /= f
        else:
            i += 1
            f = primes[i]

    if n != 1:
        a.add(n)

    return a


def bfs(graph, cap_edges, level, s, t):
    queue = deque()
    queue.append(s)

    level[s] = 1

    while queue:
        u = queue.popleft()

        for v, eid, _ in graph[u]:
            if level[v] == 0 and cap_edges[eid] > 0:
                level[v] = level[u] + 1
                queue.append(v)

    return level[t] > 0


def dfs(graph, ptr, cap_edges, level, u, s, t):
    if u == t:
        return 1

    adj = graph[u]
    ind = ptr[u]

    i = ind
    n = len(adj)
    while i < n:
        v, eid, eid_b = adj[i]
        ptr[u] = i
        i += 1

        if (level[v] == level[u] + 1) and cap_edges[eid] > 0:
            f = dfs(graph, ptr, cap_edges, level, v, s, t)
            if f > 0:
                cap_edges[eid] -= 1
                cap_edges[eid_b] += 1
                return f

    return 0


# solve the max-flow problem using the Dinic algorithm
def max_flow(graph, cap_edges, s, t):
    n = len(graph)
    level = [0] * n
    ptr = [0] * n

    flow = 0
    while bfs(graph, cap_edges, level, s, t):
        f = dfs(graph, ptr, cap_edges, level, s, s, t)

        while f > 0:
            flow += f
            f = dfs(graph, ptr, cap_edges, level, s, s, t)

        level = [0] * n
        ptr = [0] * n

    return flow


def computer_game(n, A, B):

    start_node = 0
    end_node = 1

    graph = defaultdict(list)
    cap_edges = []
    node_count = 2
    edges_count = 0
    prime_nodes_map = {}

    for value in A:
        current_node = node_count

        graph[start_node].append((current_node, edges_count, edges_count+1))
        cap_edges.append(1)
        graph[current_node].append((start_node, edges_count+1, edges_count))
        cap_edges.append(0)
        edges_count += 2
        node_count += 1

        factors = trial_division(value)

        for p in factors:
            if p not in prime_nodes_map:
                prime_nodes_map[p] = node_count
                node_count += 1

            p_node = prime_nodes_map[p]
            graph[current_node].append((p_node, edges_count, edges_count+1))
            cap_edges.append(1)

            graph[p_node].append((current_node, edges_count+1, edges_count))
            cap_edges.append(0)
            edges_count += 2

    for value in B:
        current_node = node_count

        graph[current_node].append((end_node, edges_count, edges_count+1))
        cap_edges.append(1)

        graph[end_node].append((current_node, edges_count+1, edges_count))
        cap_edges.append(0)
        edges_count += 2
        node_count += 1

        factors = trial_division(value)
        for p in factors:
            if p not in prime_nodes_map:
                prime_nodes_map[p] = node_count
                node_count += 1

            p_node = prime_nodes_map[p]
            graph[p_node].append((current_node, edges_count, edges_count+1))
            cap_edges.append(1)

            graph[current_node].append((p_node, edges_count+1, edges_count))
            cap_edges.append(0)
            edges_count += 2

    result = max_flow(graph, cap_edges, start_node, end_node)
    print(result)


if __name__ == '__main__':
    n = int(raw_input())

    a = map(int, raw_input().rstrip().split())

    b = map(int, raw_input().rstrip().split())

    computer_game(n, a, b)
