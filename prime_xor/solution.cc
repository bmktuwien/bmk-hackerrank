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
    int N = 4500;
    int W = 8192;

    vector<vector<int>> dp(N+1, vector<int>(W+1, 0));

    for (int a = 0; a <= N; a++) {
        for (int w = 0; w <= W; w++) {
            if (a == 0) {
                dp[a][w] = 0;
            } else if (w == 0) {
                dp[a][w] = 1;
            } else {
                int freq = freq_tbl[a];
                int c1 = freq / 2 + 1;
                int c2 = freq / 2 + (freq % 2);

                dp[a][w] = c1 * dp[a-1][w] + c2 * dp[a-1][w^a];
            }
        }
    }

    int ans = 0;
    for (int w = 2; w <= W; w++) {
        if (prime_tbl[w] && dp[N][w] > 0) {
            ans += dp[N][w];
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