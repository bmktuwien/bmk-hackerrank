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

    naive_solver(a, queries, k);
}