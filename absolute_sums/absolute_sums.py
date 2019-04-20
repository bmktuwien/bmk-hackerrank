#!/bin/python

import math
import os
import random
import re
import sys
from bisect import *


# Complete the playingWithNumbers function below.
def playingWithNumbers(arr, queries):
    arr = sorted(arr)
    n = len(arr)

    sums = []
    total_sum = 0
    for value in arr:
        total_sum += value
        sums.append(total_sum)

    acc = 0
    for q in queries:
        acc += q

        idx = bisect(arr, -acc)
        lo_sum = sums[idx-1] if idx > 0 else 0
        hi_sum = total_sum - lo_sum

        result = abs(lo_sum + (idx * acc))
        result += (hi_sum + ((n-idx)*acc))
        print(result)


if __name__ == '__main__':
    n = int(raw_input())

    arr = map(int, raw_input().rstrip().split())

    q = int(raw_input())

    queries = map(int, raw_input().rstrip().split())

    playingWithNumbers(arr, queries)
