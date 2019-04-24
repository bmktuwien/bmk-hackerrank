# -*- coding: utf-8 -*-

#!/bin/python

from collections import *
import random
import itertools
from fractions import *


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


def power(x, y, p):
    res = 1

    x = x % p
    while y > 0:
        if y & 1:
            res = (res * x) % p

        y = y>>1
        x = (x * x) % p

    return res


def miller_test(d, n):
    a = 2 + random.randint(1, n - 4)

    x = power(a, d, n)

    if x == 1 or x == n - 1:
        return True

    while d != n - 1:
        x = (x * x) % n
        d *= 2

        if x == 1:
            return False
        if x == n - 1:
            return True

    return False


def is_prime(n, k):
    if n == 4:
        return False
    
    if n <= 3:
        return True

    d = n - 1
    while d % 2 == 0:
        d //= 2

    for i in range(k):
        if not miller_test(d, n):
            return False

    return True


def trial_division(n):
    a = set()

    while n % 2 == 0:
        a.add(2)
        n /= 2

    f = 3

    if is_prime(n, 1):
        a.add(n)
        return a

    while f * f <= n:
        if n % f == 0:
            a.add(f)
            n /= f
        else:
            f += 2

    if n != 1:
        a.add(n)

    return a


def bfs(graph, cap_edges, level, s, t):  # C is the capacity matrix
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

    print(len(cap_edges))
    print(node_count)
    result = max_flow(graph, cap_edges, start_node, end_node)
    print(result)


if __name__ == '__main__':
    n = int(raw_input())

    a = map(int, raw_input().rstrip().split())

    b = map(int, raw_input().rstrip().split())

    computer_game(n, a, b)

