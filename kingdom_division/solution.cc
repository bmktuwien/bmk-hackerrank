#include <bits/stdc++.h>

using namespace std;

#define M 1000000007

struct Result {
    long b{-1};
    long r{-1};
    long d_b{-1};
    long d_r{-1};
    bool is_leaf{false};
};

void solve(const vector<vector<int>>& tree) {
    vector<bool> is_leaf(tree.size(), true);

    vector<Result> dp(tree.size());

    vector<int> stack;
    stack.push_back(0);

    while (!stack.empty()) {
        int city = stack.back();

        bool done = true;

        for (auto child : tree[city]) {
            if (dp[child].b == -1) {
                stack.push_back(child);
                done = false;
            }
        }

        if (done) {
            if (tree[city].empty()) {
                dp[city] = {1, 1, 0, 0, true};
            } else {
                long acc_b = 1;
                long acc_r = 1;

                bool flag = false;
                for (auto child : tree[city]) {
                    auto &res = dp[child];
                    acc_b *= res.b + (res.is_leaf ? 0 : res.r) + res.d_b;
                    acc_r *= res.r + (res.is_leaf ? 0 : res.b) + res.d_r;

                    acc_b %= M;
                    acc_r %= M;

                    flag |= res.is_leaf;
                }

                long d_b = 0;
                long d_r = 0;

                if (!flag) {
                    d_b = 1;
                    d_r = 1;

                    for (auto child : tree[city]) {
                        auto &res = dp[child];

                        d_b *= res.r;
                        d_r *= res.b;

                        d_b %= M;
                        d_r %= M;
                    }

                    acc_b -= d_b;
                    acc_r -= d_r;
                }

                acc_b %= M;
                acc_r %= M;

                acc_b = acc_b < 0 ? acc_b + M : acc_b;
                acc_r = acc_r < 0 ? acc_r + M : acc_r;

                dp[city] = {acc_b, acc_r, d_b, d_r, false};
            }

            stack.pop_back();
        }
    }

    long ans = (dp[0].b + dp[0].r) % M;
    cout << ans << endl;
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

    vector<vector<int>> tree(adj_matrix.size());
    set<int> marked;
    vector<int> stack;
    stack.push_back(0);

    while (!stack.empty()) {
        int city = stack.back();
        stack.pop_back();

        marked.insert(city);

        for (auto c : adj_matrix[city]) {
            if (marked.find(c) == marked.end()) {
                tree[city].push_back(c);
                stack.push_back(c);
            }
        }
    }

    solve(tree);
}