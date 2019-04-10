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


def calc_next_lvl(lkup1, lkup2, prev_table):
    table = {}
    res = 0

    for k, v in prev_table.iteritems():
        if k in lkup1:
            prefixes = lkup1[k]

            for prefix in prefixes:
                if prefix in table:
                    t = table[prefix]
                    table[prefix] = (t + v) % MOD
                else:
                    table[prefix] = v

        if k in lkup2:
            x = lkup2[k]
            res += (v * x)
            res = res % MOD

    return res, table


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


def lookup_tables(qs):
    result = {}
    result2 = {}

    suffixes = set()
    for q in qs:
        suffix = q % 10000
        suffixes.add(suffix)

    for q in qs:
        prefix = q / 10
        suffix = q % 10000

        if prefix in suffixes:
            if suffix in result:
                result[suffix].add(prefix)
            else:
                result[suffix] = {prefix}

        if prefix >= 1000:
            if suffix in result2:
                result2[suffix] += 1
            else:
                result2[suffix] = 1

    return result, result2


def solve(queries):
    qs = find_all_valid_quintuplets()
    lkup1, lkup2 = lookup_tables(qs)

    table = init(qs)

    max_n = max(queries)
    result_table = {
        1: 9,
        2: 90,
        3: 303,
        4: 280,
        5: 218
    }

    for n in range(6, max_n+1):
        res, table = calc_next_lvl(lkup1, lkup2, table)
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
