#include <vector>
#include <iostream>
#include <map>

std::vector<std::vector<long>> calc_freq(const std::string& inp) {
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

    return freq_map;
}

int main() {
    std::string s1;
    std::string s2;

    std::cin >> s1 >> s2;

    auto freq_map = calc_freq(s1);

    std::vector<std::pair<int,int>> cache(26, std::make_pair(0,0));

    int res = 0;
    for (int i = 0; i < 26; i++) {

    }

}
