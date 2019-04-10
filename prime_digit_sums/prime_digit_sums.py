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


def calc_next_lvl(magic_table, prev_table):
    table = {}
    res = 0

    for k, v in prev_table.iteritems():
        if k in magic_table:
            prefixes = magic_table[k]

            for prefix in prefixes:
                if prefix in table:
                    t = table[prefix]
                    table[prefix] = (t + v) % MOD
                else:
                    table[prefix] = v

                if prefix >= 1000:
                    res += v
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


def get_magic_table(qs):
    result = {}

    for q in qs:
        prefix = q / 10
        suffix = q % 10000
        if suffix in result:
            result[suffix].add(prefix)
        else:
            result[suffix] = {prefix}

    return result


def solve(queries):
    qs = find_all_valid_quintuplets()
    magic_table = get_magic_table(qs)

    table = init(qs)

    max_n = max(queries)
    result_table = {
        1: 9,
        2: 0, #TODO
        3: 0, #TODO
        4: 0, #TODO
        5: len(qs)
    }

    for n in range(6, max_n+1):
        res, table = calc_next_lvl(magic_table, table)
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
