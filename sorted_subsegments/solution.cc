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
    std::vector<std::pair<int,int>> q2;

    for (auto it = queries.rbegin(); it != queries.rend(); it++) {
        if (s.empty()) {
            if (it->first <= k && k <= it->second) {
                s.insert(*it);
                q2.push_back(*it);
            }
        } else {
            bool f1 = false;
            auto x1 = s.lower_bound(std::make_pair(it->first+1, 0));
            if (x1 != s.begin()) {
                x1--;

                if (it->first <= x1->second) {
                    f1 = true;
                }
            }

            bool f2 = false;
            auto x2 = s.lower_bound(std::make_pair(it->second+1, 0));
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
                        x1 = s.erase(x1);
                    }
                    s.erase(x2);

                    if (tmp1.first <= it->first - 1) {
                        s.insert(std::make_pair(tmp1.first, it->first-1));
                    }
                    s.insert(*it);

                    if (it->second + 1 <= tmp2.second) {
                        s.insert(std::make_pair(it->second + 1, tmp2.second));
                    }

                    q2.push_back(*it);
                }
            } else if (f1) {
                auto tmp = *x1;

                while (x1 != s.end()) {
                    x1 = s.erase(x1);
                }

                if (it->first-1 >= tmp.first) {
                    s.insert(std::make_pair(tmp.first, it->first-1));
                }
                s.insert(std::make_pair(it->first, it->second));

                q2.push_back(*it);
            } else if (f2) {
                auto tmp = *x2;

                while (x2 != s.begin()) {
                    x2 = s.erase(x2);
                    x2--;
                }
                s.erase(x2);

                s.insert(std::make_pair(it->first, it->second));
                if (it->second+1 <= tmp.second) {
                    s.insert(std::make_pair(it->second+1, tmp.second));
                }

                q2.push_back(*it);
            }
        }
    }

    std::set<std::pair<int,int>> s2;
    for (auto it = q2.rbegin(); it != q2.rend(); it++) {
        if (s2.empty()) {
            s2.insert(*it);
            std::sort(a.begin()+it->first, a.begin()+it->second+1);
        } else {
            bool f1 = false;
            auto x1 = s2.lower_bound(std::make_pair(it->first+1, 0));
            if (x1 != s2.begin()) {
                x1--;

                if (it->first <= x1->second) {
                    f1 = true;
                }
            }

            bool f2 = false;
            auto x2 = s2.lower_bound(std::make_pair(it->second+1, 0));
            if (x2 != s2.begin()) {
                x2--;

                if (it->second <= x2->second) {
                    f2 = true;
                }
            }

            if (f1 && f2) {
                if (x1 != x2) {
                    auto tmp1 = *x1;
                    auto tmp2 = *x2;

                    int count = 0;
                    while (x1 != x2) {
                        x1 = s2.erase(x1);
                        count++;
                    }
                    s2.erase(x2);

                    if (tmp1.first < it->first - 1) {
                        s2.insert(std::make_pair(tmp1.first, it->first-1));
                    }
                    s2.insert(*it);

                    if (it->second + 1 < tmp2.second) {
                        s2.insert(std::make_pair(it->second + 1, tmp2.second));
                    }

                    if (count == 1) {
                        std::inplace_merge(a.begin()+it->first, a.begin()+tmp2.first,
                                           a.begin()+it->second+1);
                    } else {
                        if (!std::is_sorted(a.begin()+it->first, a.begin()+it->second+1)) {
                            std::sort(a.begin()+it->first, a.begin()+it->second+1);
                        }
                    }
                }
            } else if (f1) {
                auto tmp = *x1;

                while (x1 != s2.end()) {
                    x1 = s2.erase(x1);
                }

                if (it->first-1 > tmp.first) {
                    s2.insert(std::make_pair(tmp.first, it->first-1));
                }
                s2.insert(std::make_pair(it->first, it->second));

                if (!std::is_sorted(a.begin()+tmp.second+1, a.begin()+it->second+1)) {
                    std::sort(a.begin()+tmp.second+1, a.begin()+it->second+1);
                }

                std::inplace_merge(a.begin()+it->first, a.begin()+tmp.second+1,
                                   a.begin()+it->second+1);
            } else if (f2) {
                auto tmp = *x2;

                while (x2 != s2.begin()) {
                    x2 = s2.erase(x2);
                    x2--;
                }
                s2.erase(x2);

                s2.insert(std::make_pair(it->first, it->second));
                if (it->second+1 < tmp.second) {
                    s2.insert(std::make_pair(it->second+1, tmp.second));
                }

                if (!std::is_sorted(a.begin()+it->first, a.begin()+tmp.first)) {
                    std::sort(a.begin()+it->first, a.begin()+tmp.first);
                }

                std::inplace_merge(a.begin()+it->first, a.begin()+tmp.first,
                                   a.begin()+it->second+1);
            } else {
                s2.insert(*it);
                std::sort(a.begin()+it->first, a.begin()+it->second+1);
            }
        }
    }

    std::cout << a[k] << std::endl;
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

    std::vector<std::pair<int,int>> queries;
    for (int i = 0; i < q; i++) {
        int l, r;
        std::cin >> l >> r;
        queries.emplace_back(std::make_pair(l, r));
    }

    solver2(a, queries, k);
}