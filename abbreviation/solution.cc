#include <bits/stdc++.h>

using namespace std;

bool go(vector<vector<int>>& dp, int i, int j, const string& a, const string& b) {
    if (j < 0) {
        return true;
    }

    if (i < 0) {
        return false;
    }

    if (dp[i][j] != -1) {
        return dp[i][j] != 0;
    }

    for (int k = i; k >= 0; k--) {
        if (toupper(a[k]) == b[j]) {
            if (go(dp, k-1, j-1, a, b)) {
                dp[i][j] = 1;
                return true;
            }
        }

        if (isupper(a[k])) {
            break;
        }
    }

    dp[i][j] = 0;
    return false;
}

void solve(string& a, string& b) {
    vector<vector<int>> dp(a.size(), vector<int>(b.size(), -1));

    if (go(dp, a.size()-1, b.size()-1, a, b)) {
        cout << "YES" << endl;
    } else {
        cout << "NO" << endl;
    }
}

int main(int argc, char **argv) {
    int q;
    cin >> q;

    while (q--) {
        string a, b;
        cin >> a >> b;

        solve(a, b);
    }
}