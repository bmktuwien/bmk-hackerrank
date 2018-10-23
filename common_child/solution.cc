#include <algorithm>
#include <vector>
#include <iostream>
#include <map>
#include <set>

using FreqMap = std::vector<std::vector<int>>;
using DPCache = std::vector<std::vector<int>>;

FreqMap calc_freq(const std::string& inp) {
    FreqMap freq_map(26);

    for (size_t i = 0; i < inp.size(); i++) {
        freq_map[inp[i]-'A'].emplace_back(i);
    }

    return freq_map;
}

int prev_pos(char c, int pos, const FreqMap& freq_map) {
    auto &v = freq_map[c-'A'];
    auto it = std::upper_bound(v.begin(), v.end(), pos+1);

    if (it == v.begin()) {
        return -1;
    } else {
        it--;
        return *(it);
    }
}

int solve(int i, int j, const std::string& s1, const std::string& s2,
          const FreqMap& freq_map1, const FreqMap& freq_map2,
          DPCache& dp_cache) {

    if (i < 0 || j < 0) {
        return 0;
    }

    if (dp_cache[i][j] != -1) {
        return dp_cache[i][j];
    }

    auto x1 = prev_pos(s1[i], j, freq_map2);
    int p1 = -1;
    if (x1 != -1) {
        p1 = solve(i-1, x1-1, s1, s2, freq_map1, freq_map2, dp_cache) + 1;
    }

    auto x2 = prev_pos(s2[j], i, freq_map1);
    int p2 = -1;
    if (x2 != -1) {
        p2 = solve(x2-1, j-1, s1, s2, freq_map1, freq_map2, dp_cache) + 1;
    }

    int p3 = solve(i-1, j, s1, s2, freq_map1, freq_map2, dp_cache);
    int p4 = solve(i, j-1, s1, s2, freq_map1, freq_map2, dp_cache);

    dp_cache[i][j] = std::max({p1,p2,p3,p4});

    return dp_cache[i][j];
}

int main() {
    std::string s1;
    std::string s2;

    std::cin >> s1 >> s2;

    DPCache dp_cache(s1.size(), std::vector<int>(s1.size(),-1));
    FreqMap freq_map1 = calc_freq(s1);
    FreqMap freq_map2 = calc_freq(s2);

    int res = solve(s1.size()-1, s2.size()-1, s1, s2, freq_map1, freq_map2, dp_cache);

    std::cout << res << std::endl;
}
