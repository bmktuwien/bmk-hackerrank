#!/bin/python

from __future__ import print_function

import os
import sys
import math


def distance_pow2(biker, bike):
    return (biker[0]-bike[0])**2 + (biker[1]-bike[1])**2


def bikeRacers(bikers, bikes, k):
    candidates = []

    for i in range(len(bikers)):
        for j in range(len(bikes)):
            candidates.append((distance_pow2(bikers[i], bikes[j]), i, j))

    candidates = sorted(candidates)
    marked_bikers = set()
    marked_bikes = set()

    count = 0
    max_distance = 0

    print(candidates)
    for d, biker, bike in candidates:
        if biker not in marked_bikers and bike not in marked_bikes:
            marked_bikers.add(biker)
            marked_bikes.add(bike)
            count += 1

            if d > max_distance:
                max_distance = d

        if count >= k:
            break

    print(max_distance)


if __name__ == '__main__':
    nmk = raw_input().split()

    n = int(nmk[0])
    m = int(nmk[1])
    k = int(nmk[2])

    bikers = []

    for _ in xrange(n):
        bikers.append(map(int, raw_input().rstrip().split()))

    bikes = []

    for _ in xrange(n):
        bikes.append(map(int, raw_input().rstrip().split()))

    bikeRacers(bikers, bikes, k)


