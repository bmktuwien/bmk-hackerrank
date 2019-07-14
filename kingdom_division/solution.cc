#include <bits/stdc++.h>

using namespace std;

pair<long,long> solve(const vector<vector<int>>& adj_matrix, set<int>& visited, int city) {
    visited.insert(city);

    bool is_leaf = true;

    vector<long> bs;
    vector<long> rs;

    for (auto neighbor : adj_matrix[city]) {
        if (visited.find(neighbor) == visited.end()) {
            is_leaf = false;
            auto p = solve(adj_matrix, visited, neighbor);
            bs.push_back(p.first);
            rs.push_back(p.second);
        }
    }

    if (is_leaf) {
        return make_pair(1, 1);
    } else {
        long acc = 1;
        for (int i = 0; i < bs.size(); i++) {
            acc *= bs[i] + rs[i];
        }

        long b_acc = 1;
        for (auto b : bs) {
            b_acc *= b;
        }

        long r_acc = 1;
        for (auto r : rs) {
            r_acc *= r;
        }

        return make_pair(acc-r_acc, acc-b_acc);
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

    set<int> visited;
    auto p = solve(adj_matrix, visited, 0);

    cout << p.first + p.second << endl;
}