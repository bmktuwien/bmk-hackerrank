#include <algorithm>
#include <vector>
#include <iostream>
#include <map>


using DPCache = std::vector<std::vector<int>>;


int solve(int i, int j, const std::string& s1, const std::string& s2,
          DPCache& dp_cache) {

    if (i < 0 || j < 0) {
        return 0;
    }

    if (dp_cache[i][j] != -1) {
        return dp_cache[i][j];
    }

    int r;

    if (s1[i] == s2[j]) {
        r = solve(i-1, j-1, s1, s2, dp_cache) + 1;
    } else {
        int p1 = solve(i-1, j, s1, s2, dp_cache);
        int p2 = solve(i, j-1, s1, s2, dp_cache);

        r = std::max(p1,p2);
    }

    dp_cache[i][j] = r;

    return dp_cache[i][j];
}

int main() {
    std::string s1;
    std::string s2;

    std::cin >> s1 >> s2;

    DPCache dp_cache(s1.size(), std::vector<int>(s1.size(),-1));

    int res = solve(s1.size()-1, s2.size()-1, s1, s2, dp_cache);

    /*for (auto &v : dp_cache) {
        std::cout << "[";
        for (auto x : v) {
            std::cout << x << ", ";
        }
        std::cout << "]" << std::endl;
        }*/

    std::cout << res << std::endl;
}
