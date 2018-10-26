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

int calc1(int x1, int x2, int n, const std::vector<std::vector<int>> &indexes) {
    int res = n;

    int d1 = indexes[x1].size() - (n/4);
    int d2 = indexes[x2].size() - (n/4);

    for (int i = 0; i+d1 <= indexes[x1].size(); i++) {
        int p0 = indexes[x1][i];
        int p1 = indexes[x1][i+d1-1];

        auto it1 = std::upper_bound(indexes[x2].begin(), indexes[x2].end(), p0);
        if (std::distance(it1, indexes[x2].end()) >= d2) {
            int q1 = std::max(p1, *(it1+d2-1));
            int t = q1-p0+1;
            if (t < res) {
                res = t;
            }
        }

        auto it2 = std::lower_bound(indexes[x2].begin(), indexes[x2].end(), p1);
        if (std::distance(indexes[x2].begin(), it2) >= d2) {
            int q0 = std::min(p0, *(it2-d2));
            int t = p1-q0+1;
            if (t < res) {
                res = t;
            }
        }
    }

    return res;
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
            std::cout << i << std::endl;
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
        int d = indexes[x1].size() - (n/4);
        for (int i = 0; i+d <= indexes[x1].size(); i++) {
            int t = indexes[x1][i+d-1] -  indexes[x1][i] + 1;
            if (t < res) {
                res = t;
            }
        }

        std::cout << res << std::endl;
    } else {
        int res = calc1(x1,x2,n,indexes);

        int t = calc1(x2,x1,n,indexes);

        if (t < res) {
            res = t;
        }

        std::cout << res << std::endl;
    }
}
