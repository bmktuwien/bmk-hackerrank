#include <bits/stdc++.h>

using namespace std;

#define M 1000000007

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
    int N = 1001;
    int W = 8192;

    vector<vector<int>> dp(N+1, vector<int>(W+1));

    for (int a = 0; a <= N; a++) {
        for (int w = 0; w <= W; w++) {
            if (a == 0) {
                dp[a][w] = w == 0 ? 1 : 0;
            } else {
                long v = 3500 + a - 1;

                int freq = freq_tbl[v];
                int c1 = freq / 2 + 1;
                int c2 = freq / 2 + (freq % 2);

                dp[a][w] = ((c1 * dp[a-1][w]) % M) + ((c2 * dp[a-1][w^v]) % M);
                dp[a][w] %= M;
            }
        }
    }

    int ans = 0;
    for (int w = 2; w <= W; w++) {
        if (prime_tbl[w] && dp[N][w] > 0) {
            ans += dp[N][w];
            ans %= M;
        }
    }

    cout << ans << endl;
}

int main(int argc, char **argv) {
    auto prime_table = gen_prime_table(8192);

    int q;
    cin >> q;

    while (q--) {
        int n;
        cin >> n;
        vector<int> freq_tbl(4501, 0);

        while (n--) {
            int i;
            cin >> i;
            freq_tbl[i]++;
        }

        solve(freq_tbl, prime_table);
    }

}