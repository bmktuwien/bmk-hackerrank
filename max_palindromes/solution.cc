#include <bits/stdc++.h>

#define MOD 1000000007L

class BITree {
public:
    explicit BITree(size_t n) : _n(n) {
        _a.resize(n+1, 0);
    }

    void update(int index, long val) {
        index = index + 1;

        while (index <= _n) {
            _a[index] += val;
            index += index & (-index);
        }
    }

    long getSum(int index) {
        long sum = 0;
        index = index + 1;

        while (index>0) {
            sum += _a[index];
            index -= index & (-index);
        }

        return sum;
    }

private:
    size_t _n;
    std::vector<long> _a;
};

long n_choose_k(int n, int k) {
    if (n < k) {
        return 0;
    }

    long res = 1;

    if (k > n - k) {
        k = n - k;
    }

    for (int i = 0; i < k; ++i) {
        res *= (n - i);
        res /= (i + 1);
    }

    return res;
}

int main() {
    std::string s;
    int q;

    std::cin >> s >> q;

    std::vector<BITree> treeMap;
    for (int i = 0; i < 26; i++) {
        treeMap.emplace_back(BITree(s.size()));
    }

    for (int i = 0; i < s.size(); i++) {
        treeMap[s[i]-'a'].update(i, 1);
    }

    while (q--) {
        int l, r;

        std::cin >> l >> r;
        std::vector<long> x(26, 0);
        long t = 0;

        for (int i = 0; i < 26; i++) {
            auto cnt = treeMap[i].getSum(r-1) - (l > 1 ? treeMap[i].getSum(l-2) : 0);

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

                result *= n_choose_k(acc, n);
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