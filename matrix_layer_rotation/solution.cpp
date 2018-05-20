//
// Created by bmk on 5/20/18.
//

#include <bits/stdc++.h>

void matrix_layer_rotation(const std::vector<std::vector<int>>& M, size_t r) {
    int n = M.size();
    int m = M[0].size();

    int l = 0;
    while (std::min<int>(n,m) - (2*l) > 0) {
        std::cout << "layer: " << l << std::endl;

        {
            int j = l;
            for (int i = l; i < n - l; i++) {
                std::cout << M[i][j] << " ";
            }
            std::cout << std::endl;
        }

        {
            int j = m - l - 1;
            for (int i = l; i < n - l; i++) {
                std::cout << M[i][j] << " ";
            }
            std::cout << std::endl;
        }

        {
            int i = l;
            for (int j = l + 1; j < m - l - 1; j++) {
                std::cout << M[i][j] << " ";
            }
            std::cout << std::endl;
        }

        {
            int i = n - l - 1;
            for (int j = l + 1; j < m - l - 1; j++) {
                std::cout << M[i][j] << " ";
            }
            std::cout << std::endl;
        }





        l++;
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