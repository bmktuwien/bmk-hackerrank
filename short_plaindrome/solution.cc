#include <algorithm>
#include <iostream>
#include <map>
#include <vector>
#include <set>

const long M = 1000000007;

long calc0(const std::vector<int> &v) {
    long res = 0;

    if (v.empty()) {
        return 0;
    }

    long s = 0;
    for (int i = 1; i < v.size(); i++) {
        long t = v.size()-i-1;
        s += i-1;

        res += (s*t);
        res %= M;
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
        res += calc0(indexes[i]);

        for (int j = i+1; j < 26; j++) {
            res += calc(indexes[i], indexes[j]);
            res += calc(indexes[j], indexes[i]);
        }

        res %= M;
    }

    std::cout << res << std::endl;
}
