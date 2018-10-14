#include <vector>
#include <iostream>

std::vector<int> calc_sig(int r, int l,
                          const std::vector<std::vector<long>>& freq_map) {
    std::vector<int> sig(26);

    for (int i = 0; i < 26; i++) {
        auto cnt = freq_map[i][r] - (l > 0 ? freq_map[i][l-1] : 0);
        sig[i] = cnt;
    }

    return sig;
}

void count_anagrams(const std::string& inp) {
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

    for (size_t w = 0; w < l-1; w++) {
        for (auto i = 0; i+w < l; i++) {

        }

        std::cout << std::endl;
    }
}

int main() {
    int q;

    std::cin >> q;

    while (q--) {
        std::string s;
        std::cin >> s;

        count_anagrams(s);
    }
}
