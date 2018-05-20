//
// Created by bmk on 5/20/18.
//

#include <bits/stdc++.h>

void matrix_layer_rotation(const std::vector<std::vector<int>>& M, size_t r) {
    auto n = M.size();
    auto m = M[0].size();

    std::vector<std::vector<int>> ans;
    ans.resize(n);
    for (auto &v : ans) {
        v.resize(m);
    }

    int l = 0;
    while (std::min<int>(n,m) - (2*l) > 0) {
        auto p = n - (2 * l);
        auto q = m - (2 * l);
        auto x = (p + q) * 2 - 4;
        auto y = r % x;

        {
            int j = l;
            for (int i = l; i < n - l; i++) {
                auto tmp = y;
                auto z = n - l - i;
                if (tmp < z) {
                    ans[i+tmp][j] = M[i][j];
                    continue;
                }
                tmp -= (z-1);

                if (tmp < q) {
                    ans[n-l-1][l+tmp] = M[i][j];
                    continue;
                }
                tmp -= (q-1);

                if (tmp < p) {
                    ans[n-l-1-tmp][m-l-1] = M[i][j];
                    continue;
                }
                tmp -= (p-1);

                if (tmp < q) {
                    ans[l][m-1-l-tmp] = M[i][j];
                    continue;
                }
                tmp -= (q-1);

                if (tmp > 0) {
                    ans[l+tmp][l] = M[i][j];
                }
            }
        }

        {
            int j = m - l - 1;
            for (int i = l; i < n - l; i++) {
                auto tmp = y;
                auto z = i - l + 1;
                if (tmp < z) {
                    ans[i-tmp][j] = M[i][j];
                    continue;
                }
                tmp -= (z-1);

                if (tmp < q) {
                    ans[l][m-1-l-tmp] = M[i][j];
                    continue;
                }
                tmp -= (q-1);

                if (tmp < p) {
                    ans[l+tmp][l] = M[i][j];
                    continue;
                }
                tmp -= (p-1);

                if (tmp < q) {
                    ans[n-l-1][l+tmp] = M[i][j];
                    continue;
                }
                tmp -= (q-1);

                if (tmp > 0) {
                    ans[n-l-1-tmp][m-l-1] = M[i][j];
                }
            }
        }

        {
            int i = l;
            for (int j = l + 1; j < m - l - 1; j++) {
                auto tmp = y;
                auto z = j - l + 1;
                if (tmp < z) {
                    ans[i][j-tmp] = M[i][j];
                    continue;
                }
                tmp -= (z-1);

                if (tmp < p) {
                    ans[l+tmp][l] = M[i][j];
                    continue;
                }
                tmp -= (p-1);

                if (tmp < q) {
                    ans[n-l-1][l+tmp] = M[i][j];
                    continue;
                }
                tmp -= (q-1);

                if (tmp < p) {
                    ans[n-l-1-tmp][m-l-1] = M[i][j];
                    continue;
                }
                tmp -= (p-1);

                if (tmp > 0) {
                    ans[i][m-1-l-tmp] = M[i][j];
                }
            }
        }

        {
            int i = n - l - 1;
            for (int j = l + 1; j < m - l - 1; j++) {
                auto tmp = y;
                auto z = m - l - j;
                if (tmp < z) {
                    ans[i][j+tmp] = M[i][j];
                    continue;
                }
                tmp -= (z-1);

                if (tmp < p) {
                    ans[n-l-1-tmp][m-l-1] = M[i][j];
                    continue;
                }
                tmp -= (p-1);

                if (tmp < q) {
                    ans[l][m-1-l-tmp] = M[i][j];
                    continue;
                }
                tmp -= (q-1);

                if (tmp < p) {
                    ans[l+tmp][l] = M[i][j];
                    continue;
                }
                tmp -= (p-1);

                if (tmp > 0) {
                    ans[i][l+tmp] = M[i][j];
                }
            }
        }

        l++;
    }

    for (auto &v : ans) {
        for (auto num : v) {
            std::cout << num << " ";
        }
        std::cout << std::endl;
    }
}

int main(int argc, char **argv) {
    size_t n, m, r;
    std::cin >> n >> m >> r;

    std::vector<std::vector<int>> M;
    M.resize(n);

    for (auto i = 0; i < n; i++) {
        M[i].resize(m);
        for (auto j = 0; j < m; j++) {
            std::cin >> M[i][j];
        }
    }

    matrix_layer_rotation(M, r);
}