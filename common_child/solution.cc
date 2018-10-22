#include <algorithm>
#include <vector>
#include <iostream>
#include <map>
#include <set>

using FreqMap = std::vector<std::vector<long>>;

FreqMap calc_freq(const std::string& inp) {
    FreqMap freq_map(26);

    for (size_t i = 0; i < inp.size(); i++) {
        freq_map[inp[i]-'A'].emplace_back(i);
    }

    return freq_map;
}

int next_pos(char c, int pos, const FreqMap& freq_map) {
    auto &v = freq_map[c-'A'];
    auto it = std::lower_bound(v.begin(), v.end(), pos+1);

    if (it != v.end()) {
        return *it;
    } else {
        return -1;
    }
}


int main() {
    std::string s1;
    std::string s2;

    std::cin >> s1 >> s2;

    auto freq_map = calc_freq(s1);

    std::set<std::pair<int,int>> s;
    s.insert(std::make_pair(0,-1));


    int res = 0;

    for (int i = 0; i < s2.size(); i++) {
        std::vector<std::pair<int,int>> v;

        for (const auto& p : s) {
            int q = next_pos(s2[i], p.second, freq_map);
            if (q != -1) {
                int r = p.first+1;
                v.push_back(std::make_pair(r,q));

                if (r > res) {
                    res = r;
                }
            }
        }

        for (const auto& p : v) {
            s.insert(p);
        }
    }

    /*for (int j = 0; j < dp_map1.size(); j++) {
        std::cout << "[" << dp_map1[j] << "," << dp_map2[j] << "] ";
    }
    std::cout << std::endl;*/
    std::cout << res << std::endl;
}
