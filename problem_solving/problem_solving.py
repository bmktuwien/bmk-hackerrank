# -*- coding: utf-8 -*-

from collections import *
import random

def go(i, g, m):
    if i in m:
        return m[i]

    candidates = g[i]

    result = 1

    for c in candidates:
        t = go(c, g, m) + 1
        if t > result:
            result = t

    m[i] = result

    return result


def problem_solving(n, k, v):
    g = defaultdict(list)

    for i in range(n):
        for j in range(i):
            if abs(v[i]-v[j]) >= k:
                g[j].append(i)

    m = {}
    for i in range(n):
        go(i, g, m)

    result = 0
    marked = {}
    for i in range(n):
        if i not in marked:
            marked[i] = result

            neighbors = [x for x in g[i] if x not in marked]

            neighbor = None

            if neighbors:
                x = max([m[neighbor] for neighbor in neighbors])
                max_neighbors = [neighbor for neighbor in neighbors if m[neighbor] == x]
                print(max_neighbors)

                if len(max_neighbors) == 1:
                    neighbor = max_neighbors[0]
                else:
                    neighbor = random.choice(max_neighbors)

            while neighbor is not None:
                marked[neighbor] = result

                neighbors = [x for x in g[neighbor] if x not in marked]
                neighbor = None

                if neighbors:
                    x = max([m[neighbor] for neighbor in neighbors])
                    max_neighbors = [neighbor for neighbor in neighbors if m[neighbor] == x]
                    print(max_neighbors)

                    if len(max_neighbors) == 1:
                        neighbor = max_neighbors[0]
                    else:
                        neighbor = random.choice(max_neighbors)

            result += 1

    print(result)


if __name__ == '__main__':
    t = int(raw_input())

    for _ in range(t):
        nk = raw_input().split()

        n = int(nk[0])

        k = int(nk[1])

        v = map(int, raw_input().rstrip().split())

        problem_solving(n, k, v)
