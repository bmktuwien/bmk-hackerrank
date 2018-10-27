#include <algorithm>
#include <iostream>
#include <map>
#include <vector>
#include <set>

const long M = 1000000007;

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

    //std::cout << "n=" << n << std::endl;
    return res;
}

long calc_stupid(const std::vector<int> &v1, const std::vector<int> &v2) {
    long res = 0;

    for (int i = 0; i < v1.size(); i++) {
        for (int j = i+1; j < v1.size(); j++) {
            int c = 0;
            for (int k = 0; k < v2.size(); k++) {
                if (v2[k] > v1[i] && v2[k] < v1[j]) {
                    c++;
                }
            }

            if (c > 1) {
                res += ((c*(c-1))/2);
                res %= M;
            }
        }
    }

    return res;
}

long calc(const std::vector<int> &v1, const std::vector<int> &v2) {
    long res = 0;

    if (v1.empty() || v2.empty()) {
        return 0;
    }

    std::vector<int> ls;
    std::vector<int> us;

    for (int i = 0; i < v1.size(); i++) {
        auto it1 = std::lower_bound(v2.begin(), v2.end(), v1[i]);
        ls.push_back(std::distance(v2.begin(), it1));

        auto it2 = std::upper_bound(v2.begin(), v2.end(), v1[i]);
        us.push_back(std::distance(it2, v2.end()));
    }

    long s = 0;
    for (int i = 1; i < v1.size(); i++) {
        long t = us[i];
        s += ls[i-1];

        res += (s*t);
        res %= M;
    }

    return res;
}


int main() {
    std::string input;
    std::cin >> input;

    std::vector<std::vector<int>> indexes(26);
    for (int i = 0; i < input.size(); i++) {
        indexes[input[i]-'a'].push_back(i);
    }

    long res = 0;
    for (int i = 0; i < 26; i++) {
        res += n_choose_k(indexes[i].size(), 4);

        for (int j = i+1; j < 26; j++) {
            res += calc(indexes[i], indexes[j]);
            res += calc(indexes[j], indexes[i]);
        }

        res %= M;
    }

    std::cout << res << std::endl;
}
