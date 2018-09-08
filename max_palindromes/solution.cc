#include <vector>
#include <iostream>

#define MOD 1000000007L

long mod_exp(long b, long e) {
    long r = 1;

    while (e > 0) {
        if ((e & 1) == 1) {
            r = (r * b) % MOD;
        }

        b = (b * b) % MOD;
        e >>= 1;
    }

    return r;
}

long n_choose_k(int n, int k, const std::vector<long> &fact_map, const std::vector<long> &inv_map) {
    if (n < k) {
        return 0;
    }

    if (k > n - k) {
        k = n - k;
    }

    long l1 = fact_map[n];
    long l2 = (inv_map[k] * inv_map[n-k]) % MOD;

    return (l1 * l2) % MOD;
}

int main() {
    std::string s;
    int q;

    std::cin >> s >> q;

    std::vector<std::vector<long>> freq_map;
    std::vector<long> fact_map(s.size()+1);
    std::vector<long> inv_map(s.size()+1);

    for (int i = 0; i < 26; i++) {
        freq_map.emplace_back(std::vector<long>(s.size(), 0));
    }

    std::vector<long> acc_map(26, 0);
    for (int i = 0; i < s.size(); i++) {
        acc_map[s[i]-'a']++;

        for (int j = 0; j < 26; j++) {
            freq_map[j][i] = acc_map[j];
        }
    }

    fact_map[0] = 1;
    inv_map[0] = 1;
    for (int i = 1; i <= s.size(); i++) {
        fact_map[i] = (i * fact_map[i-1]) % MOD;
        inv_map[i] = mod_exp(fact_map[i], MOD-2) % MOD;
    }

    while (q--) {
        int l, r;

        std::cin >> l >> r;
        std::vector<long> x(26, 0);
        long t = 0;

        for (int i = 0; i < 26; i++) {
            auto cnt = freq_map[i][r-1] - (l > 1 ? freq_map[i][l-2] : 0);

            if (cnt == 1) {
                t++;
            } else if (cnt > 1) {
                if (cnt % 2 == 0) {
                    x[i] = cnt;
                } else {
                    x[i] = cnt - 1;
                    t++;
                }
            }
        }

        long result = 1;
        long acc = 0;
        for (auto n : x) {
            if (n > 0) {
                n /= 2;
                acc += n;

                result *= n_choose_k(acc, n, fact_map, inv_map);
                result = result % MOD;
            }
        }

        if (t > 0) {
            result *= t;
            result = result % MOD;
        }

        std::cout << result << std::endl;
    }
}