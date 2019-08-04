#include <bits/stdc++.h>

using namespace std;


vector<bool> gen_prime_table(int n) {
    vector<bool> prime(n+1, true);


    for (int p = 2; p * p <= n; p++) {
        if (prime[p]) {
            for (int i = p * 2; i <= n; i += p)
                prime[i] = false;
        }
    }

    return prime;
}

void solve(const vector<int>& freq_tbl, const vector<bool>& prime_tbl) {
    int N = 1000;
    int W = 8192;

    int dp[N+1][W+1];

    for (int i = 0; i <= N; i++) {
        int a = 3500 + i - 1;

        for (int j = 0; j <= W; j++) {
            if (i == 0) {
                dp[i][j] = 0;
            } else {
                dp[i][j] = dp[i-1][j^a] + dp[i-1][j];
            }
        }
    }
}

int main(int argc, char **argv) {
    auto prime_table = gen_prime_table(8192);

}