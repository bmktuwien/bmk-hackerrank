#include <vector>
#include <iostream>
#include <map>

std::vector<int> calc_sig(int l, int r,
                          const std::vector<std::vector<long>>& freq_map) {
    std::vector<int> sig(26);

    for (int i = 0; i < 26; i++) {
        sig[i] = freq_map[i][r] - (l > 0 ? freq_map[i][l-1] : 0);
    }

    return sig;
}

long count_anagrams(const std::string& inp) {
    std::vector<std::vector<long>> freq_map;

    auto l = inp.length();

    for (int i = 0; i < 26; i++) {
        freq_map.emplace_back(std::vector<long>(inp.size(), 0));
    }

    std::vector<long> acc_map(26, 0);
    for (size_t i = 0; i < inp.size(); i++) {
        acc_map[inp[i]-'a']++;

        for (int j = 0; j < 26; j++) {
            freq_map[j][i] = acc_map[j];
        }
    }

    long result = 0;

    for (size_t w = 0; w < l-1; w++) {
        std::map<std::vector<int>, int> cnt_map;

        for (auto i = 0; i+w < l; i++) {
            auto sig = calc_sig(i, i+w, freq_map);
            cnt_map[sig] += 1;
        }

        for (const auto &p : cnt_map) {
            if (p.second > 1) {
                result += (p.second * (p.second-1)) / 2;
            }
        }
    }

    return result;
}

int main() {
    int q;

    std::cin >> q;

    while (q--) {
        std::string s;
        std::cin >> s;

        auto r = count_anagrams(s);
        std::cout << r << std::endl;
    }
}
