#include <bits/stdc++.h>

using namespace std;


void solve(vector<int>& input) {
    vector<int> dp(input[0], 0);

    for (int i = 1; i < input.size(); i++) {
        int e = input[i];

        int acc1 = numeric_limits<int>::min();
        for (int j = 0; j < dp.size(); j++) {
            if (dp[j]-j > acc1) {
                acc1 = dp[j]-j;
            }
        }

        int acc2 = numeric_limits<int>::min();;
        for (int j = dp.size()-1; j >= 0; j--) {
            if (dp[j]+j > acc2) {
                acc2 = dp[j]+j;
            }
        }

        vector<int> tmp;

        for (int j = 0; j < e; j++) {
            int m = max(acc1+j, acc2-j);
            tmp.push_back(m);
        }

        dp = move(tmp);
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

