#include <bits/stdc++.h>

using namespace std;

#define M 1000000007

struct Result {
    long b;
    long r;
    long d_b;
    long d_r;
    bool is_leaf;
};

Result solve(const vector<vector<int>>& adj_matrix, set<int>& visited, int city) {
    visited.insert(city);

    bool is_leaf = true;

    vector<Result> rs;

    for (auto neighbor : adj_matrix[city]) {
        if (visited.find(neighbor) == visited.end()) {
            is_leaf = false;
            auto res = solve(adj_matrix, visited, neighbor);
            rs.push_back(res);
        }
    }

    if (is_leaf) {
        return {1, 1, 0, 0, true};
    } else {
        long acc_b = 1;
        long acc_r = 1;

        bool flag = false;
        for (auto &res : rs) {
            acc_b *= res.b + (res.is_leaf ? 0 : res.r) + res.d_b;
            acc_r *= res.r + (res.is_leaf ? 0 : res.b) + res.d_r;

            //acc_b %= M;
            //acc_r %= M;

            flag |= res.is_leaf;
        }

        long d_b = 0;
        long d_r = 0;

        if (!flag) {
            d_b = 1;
            d_r = 1;

            for (auto &res : rs) {
                d_b *= res.r;
                d_r *= res.b;

                //d_b %= M;
                //d_r %= M;
            }

            acc_b -= d_b;
            acc_r -= d_r;
        }

        return {acc_b, acc_r, d_b, d_r, false};
    }
}

int main(int argc, char **argv) {
    int n;
    cin >> n;

    vector<vector<int>> adj_matrix(n);

    for (int i = 0; i < n-1; i++) {
        int u, v;
        cin >> u >> v;

        adj_matrix[u-1].push_back(v-1);
        adj_matrix[v-1].push_back(u-1);
    }


    /*set<int> visited;
    auto r = solve(adj_matrix, visited, 0);
    cout << r.b + r.r << endl;*/
}