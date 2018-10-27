#include <algorithm>
#include <iostream>
#include <map>
#include <vector>
#include <set>


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
            }
        }
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
        for (int j = i+1; j < 26; j++) {

            res += calc_stupid(indexes[i], indexes[j]);
            res += calc_stupid(indexes[j], indexes[i]);
        }
    }

    std::cout << res << std::endl;
}
