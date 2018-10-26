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

int calc2(int x1, int x2, int x3, int n, const std::vector<std::vector<int>> &indexes) {
    int res = n;

    int d1 = indexes[x1].size() - (n/4);
    int d2 = indexes[x2].size() - (n/4);
    int d3 = indexes[x3].size() - (n/4);

    for (int i = 0; i+d1 <= indexes[x1].size(); i++) {
        int p0 = indexes[x1][i];
        int p1 = indexes[x1][i+d1-1];

        auto it1 = std::upper_bound(indexes[x2].begin(), indexes[x2].end(), p0);
        auto it2 = std::upper_bound(indexes[x3].begin(), indexes[x3].end(), p0);
        auto it3 = std::lower_bound(indexes[x2].begin(), indexes[x2].end(), p1);
        auto it4 = std::lower_bound(indexes[x3].begin(), indexes[x3].end(), p1);

        if (std::distance(it1, indexes[x2].end()) >= d2 &&
            std::distance(it2, indexes[x3].end()) >= d3) {
            int q1 = std::max({p1,*(it1+d2-1),*(it2+d3-1)});
            int t = q1-p0+1;

            if (t < res) {
                res = t;
            }
        }

        if (std::distance(it1, indexes[x2].end()) >= d2 &&
            std::distance(indexes[x3].begin(), it4) >= d3) {
            int q0 = std::min({p0,*(it4-d3)});
            int q1 = std::max({p1,*(it1+d2-1)});
            int t = q1-q0+1;

            if (t < res) {
                res = t;
            }
        }

        if (std::distance(indexes[x2].begin(), it3) >= d2 &&
            std::distance(indexes[x3].begin(), it4) >= d3) {
            int q0 = std::min({p0,*(it3-d2),*(it4-d3)});

            int t = p1-q0+1;
            if (t < res) {
                res = t;
            }
        }

        if (std::distance(indexes[x2].begin(), it3) >= d2 &&
            std::distance(it2, indexes[x3].end()) >= d3) {
            int q0 = std::min({p0,*(it3-d2)});
            int q1 = std::max({p1,*(it2+d3-1)});

            int t = q1-q0+1;
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
    int x3 = -1;

    for (int i = 0; i < 4; i++) {
        if (indexes[i].size() > (n/4)) {
            std::cout << i << std::endl;
            if (x1 == -1) {
                x1 = i;
            } else if (x2 == -1) {
                x2 = i;
            } else {
                x3 = i;
            }
        }
    }

    if (x1 == -1 && x2 == -1 && x3 == -1) {
        std::cout << 0 << std::endl;
    } else if (x2 == -1 && x3 == -1) {
        int res = n;
        int d = indexes[x1].size() - (n/4);
        for (int i = 0; i+d <= indexes[x1].size(); i++) {
            int t = indexes[x1][i+d-1] -  indexes[x1][i] + 1;
            if (t < res) {
                res = t;
            }
        }

        std::cout << res << std::endl;
    } else if (x3 == -1) {
        int t1 = calc1(x1,x2,n,indexes);
        int t2 = calc1(x2,x1,n,indexes);

        int res = std::min(t1,t2);

        std::cout << res << std::endl;
    } else {
        int t1 = calc2(x1,x2,x3,n,indexes);
        int t2 = calc2(x2,x1,x3,n,indexes);
        int t3 = calc2(x3,x1,x2,n,indexes);

        int res = std::min({t1,t2,t3});

        std::cout << res << std::endl;
    }
}
