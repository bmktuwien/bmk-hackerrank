#include <iostream>
#include <vector>
#include <algorithm>


int char_to_int(char c) {
    if (c == 'A') {
        return 0;
    } else if (c == 'C') {
        return 1;
    } else if (c == 'G') {
        return 2;
    } else {
        return 3;
    }
}

int main() {
    int n;
    std::string input;

    std::cin >> n >> input;

    std::vector<std::vector<int>> indexes(4, std::vector<int>());

    for (int i = 0; i < n; i++) {
        indexes[char_to_int(input[i])].push_back(i);
    }

    int x1 = -1;
    int x2 = -1;
    for (int i = 0; i < 4; i++) {
        if (indexes[i].size() > (n/4)) {
            if (x1 == -1) {
                x1 = i;
            } else {
                x2 = i;
            }
        }
    }

    if (x1 == -1) {
        std::cout << 0 << std::endl;
    } else if (x2 == -1) {
        int res = n;
        int d = indexes[x1].size() - (input.size()/4);
        for (int i = 0; i+d <= indexes[x1].size(); i++) {
            int t = indexes[x1][i+d-1] -  indexes[x1][i] + 1;
            if (t < res) {
                res = t;
            }
        }

        std::cout << res << std::endl;
    }
}
