# -*- coding: utf-8 -*-

MOD = 1000000007


def is_prime(n):
    if n > 45:
        raise NotImplementedError

    return n in [2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43]


def init(qs):
    res = {}
    
    for q in qs:
        q /= 10
        if q in res:
            res[q] += 1
        else:
            res[q] = 1

    return res


def calc_next_lvl(qs, prev_cache):
    cache = {}
    res = 0

    for q in qs:
        a = q / 10
        b = q % 10000

        k = 0
        if a in cache:
            k = cache[a]

        if b in prev_cache:
            k += prev_cache[b]

            if a >= 1000:
                res += prev_cache[b]
                res = res % MOD

        k = k % MOD
        if k > 0:
            cache[a] = k

    return res, cache


def find_all_valid_quintuplets():
    result = []

    for i1 in xrange(10):
        for i2 in xrange(10):
            for i3 in xrange(10):
                for i4 in xrange(10):
                    for i5 in xrange(10):
                        if (is_prime(i1+i2+i3) and
                                is_prime(i2+i3+i4) and
                                is_prime(i3+i4+i5) and
                                is_prime(i1+i2+i3+i4) and
                                is_prime(i2+i3+i4+i5) and
                                is_prime(i1+i2+i3+i4+i5)):
                            result.append(int(''.join(map(str, [i1, i2, i3, i4, i5]))))

    return result


def solve(queries):
    qs = find_all_valid_quintuplets()

    cache = init(qs)

    max_n = max(queries)
    result_table = {
        1: 9,
        2: 0,
        3: 0,
        4: 0,
        5: len(qs)
    }

    for n in range(6, max_n+1):
        res, cache = calc_next_lvl(qs, cache)
        result_table[n] = res

    for q in queries:
        print(result_table[q])


if __name__ == '__main__':
    q = int(raw_input())

    queries = []
    for _ in range(q):
        n = int(raw_input())
        queries.append(n)

    solve(queries)

