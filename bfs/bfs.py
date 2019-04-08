# -*- coding: utf-8 -*-
from __future__ import absolute_import, print_function, unicode_literals, division

import sys


def bfs(n, m, edges, s):
    adjacency_map = {}

    # build adjacency map
    for e in edges:
        if e[0] not in adjacency_map:
            adjacency_map[e[0]] = set()
        if e[1] not in adjacency_map:
            adjacency_map[e[1]] = set()

        adjacency_map[e[0]].add(e[1])
        adjacency_map[e[1]].add(e[0])

    marked = {}
    todo = [s]
    lvl = 0

    while todo:
        for node in todo:
            marked[node] = lvl

        new_todo = []
        for node in todo:
            neighbors = adjacency_map.get(node, [])

            for neighbor in neighbors:
                if neighbor not in marked:
                    new_todo.append(neighbor)

        todo = new_todo
        lvl += 6

    for i in xrange(n):
        if i+1 != s:
            if i+1 in marked:
                sys.stdout.write(str(marked[i+1]))
            else:
                sys.stdout.write(str(-1))

            sys.stdout.write(' ')
        
    print()


if __name__ == '__main__':
    q = int(raw_input())

    for i in xrange(q):
        nm = raw_input().split()

        n = int(nm[0])
        m = int(nm[1])

        edges = []

        for _ in xrange(m):
            edges.append(map(int, raw_input().rstrip().split()))

        s = int(raw_input())

        bfs(n, m, edges, s)
