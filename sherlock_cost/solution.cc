#include <bits/stdc++.h>

using namespace std;

void solve(vector<int>& input) {
    vector<int> dp(input[0], 0);

    for (int i = 1; i < input.size(); i++) {
        vector<int> dp2;

        int e = input[i];

        for (int q = 1; q <= e; q++) {
            int max = 0;

            for (int r = 0; r < dp.size(); r++) {
                if (abs(q-r-1)+dp[r] > max) {
                    max = abs(q-r-1)+dp[r];
                }
            }

            dp2.push_back(max);
        }

        dp = move(dp2);
    }

    cout << *max_element(dp.begin(), dp.end()) << endl;
}

int main(int argc, char** argv) {
    int t;
    cin >> t;

    while (t--) {
        int n;
        cin >> n;

        vector<int> input;
        for (int i = 0; i < n; i++) {
            int k;
            cin >> k;

            input.push_back(k);
        }

        solve(input);
    }
}

