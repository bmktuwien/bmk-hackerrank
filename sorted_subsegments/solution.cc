//
// Created by bmk on 25.05.18.
//

#include <bits/stdc++.h>

void naive_solver(std::vector<int>& a,
                  std::vector<std::pair<int,int>> &queries, int k) {
        for (auto q : queries) {
            std::sort(a.begin()+q.first, a.begin()+q.second+1);
        }

        std::cout << a[k] << std::endl;
}

void solver2(std::vector<int>& a,
             std::vector<std::pair<int,int>> &queries, int k) {

    std::set<std::pair<int,int>> s;

    for (auto it = queries.rbegin(); it != queries.rend(); it++) {
        if (s.empty()) {
            if (it->first <= k && k <= it->second) {
                s.insert(*it);
            }
        } else {
            bool f1 = false;
            auto x1 = s.upper_bound(std::make_pair(it->first, it->first));
            if (x1 != s.begin()) {
                f1 = true;
                x1--;
            }

            bool f2 = false;
            auto x2 = s.lower_bound(std::make_pair(it->second+1, it->second+1));
            if (x2 != s.begin()) {
                x2--;
                if (it->second <= x2->second) {
                    f2 = true;
                }
            }

            if (f1 && f2) {
                if (x1 != x2) {
                    auto tmp1 = *x1;
                    auto tmp2 = *x2;

                    while (x1 != x2) {
                        s.erase(x1);
                        x1++;
                    }
                    s.erase(x2);

                    if (tmp1.first <= it->first - 1) {
                        s.insert(std::make_pair(tmp1.first, it->first-1));
                    }

                    s.insert(*it);

                    if (it->second + 1 <= tmp2.second) {
                        s.insert(std::make_pair(it->second + 1, tmp2.second));
                    }
                }
            } else if (f1) {
                auto tmp = *x1;

                while (x1 != s.end()) {
                    s.erase(x1);
                    x1++;
                }

                s.insert(std::make_pair(tmp.first, it->first-1));
                s.insert(std::make_pair(it->first, tmp.second));
                s.insert(std::make_pair(tmp.second+1, it->second));
            } else if (f2) {
                auto tmp = *x2;

                while (x2 != s.begin()) {
                    s.erase(x2);
                    x2--;
                }
                s.erase(x2);

                s.insert(std::make_pair(it->first, tmp.first-1));
                s.insert(std::make_pair(tmp.first, it->second));
                s.insert(std::make_pair(it->second+1, tmp.second));
            }
        }

        std::cout << "s-debug: ";
        for (auto it1 = s.begin(); it1 != s.end(); it1++) {
            std::cout << "[" << it1->first << "-" << it1->second << "] ";
        }
        std::cout << std::endl;
    }
}

int main() {
    int n, q, k;

    std::cin >> n >> q >> k;

    std::vector<int> a;
    for (int i = 0; i < n; i++) {
        int j;
        std::cin >> j;
        a.push_back(j);
    }

    std::sort(a.begin(), a.end());
    std::vector<std::pair<int,int>> queries;
    for (int i = 0; i < q; i++) {
        int l, r;
        std::cin >> l >> r;
        queries.emplace_back(std::make_pair(l, r));
    }

    solver2(a, queries, k);
}