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

    std::vector<int> ls(v1.size());
    std::vector<int> us(v1.size());

    int c1 = 0;
    int j1 = 0;
    for (int i = 0; i < v1.size(); i++) {
        while (j1 < v2.size() && v2[j1] < v1[i]) {
            c1++;
            j1++;
        }
        ls[i] = c1;
    }

    int c2 = 0;
    int j2 = v2.size() - 1;
    for (int i = v1.size()-1; i >= 0; i--) {
        while (j2 >= 0 && v2[j2] > v1[i]) {
            c2++;
            j2--;
        }
        us[i] = c2;
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
