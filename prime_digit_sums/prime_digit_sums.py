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
        res[q] = res.get(q, 0) + 1

    return res


def calc_next_lvl(qs, n, prev_cache):
    res = {}

    for q in qs:
        a = q / 10
        b = q % 10000
        res[a] = (res.get(a, 0) + prev_cache.get(b, 0)) % MOD

    return res


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


def check(n):
    digits = []
    while n >= 10:
        digits.append(n%10)
        n /= 10

    digits.append(n)

    if len(digits) >= 5:
        for i in xrange(len(digits)-2):
            if not is_prime(digits[i]+digits[i+1]+digits[i+2]):
                return False
        for i in xrange(len(digits)-3):
            if not is_prime(digits[i]+digits[i+1]+digits[i+2]+digits[i+3]):
                return False
        for i in xrange(len(digits)-4):
            if not is_prime(digits[i]+digits[i+1]+digits[i+2]+digits[i+3]+digits[i+4]):
                return False
            
        return True
    else:
        return False


def solve(q, n):
    qs = find_all_valid_quintuplets()

    cache = init(qs)

    for i in xrange(6, n+1):
        cache = calc_next_lvl(qs, i, cache)

    res = 0
    for k, v in cache.iteritems():
        if k >= 1000:
            res += v

    print(res)


if __name__ == '__main__':
    q = int(raw_input())
    n = int(raw_input())

    solve(q, n)

