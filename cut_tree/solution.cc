#include <bits/stdc++.h>

using namespace std;

int calc_weight_sums(const vector<int>& w, const vector<vector<int>>& t,
                     int v, vector<int>& sums, vector<bool>& visited) {
    visited[v] = true;
    int sum = 0;
    for (int v1 : t[v]) {
        if (visited[v1]) {
            continue;
        }

        sum += calc_weight_sums(w, t, v1, sums, visited);
    }

    sum += w[v];
    sums[v] = sum;

    return sum;
}

int main(int argc, char** argv) {
    int n;
    cin >> n;

    vector<int> w;
    for (int i = 0; i < n; i++) {
        int j;
        cin >> j;
        w.push_back(j);
    }

    vector<vector<int>> t(n, vector<int>());
    for (int i = 0; i < n-1; i++) {
        int a, b;
        cin >> a >> b;
        t[a-1].push_back(b-1);
        t[b-1].push_back(a-1);
    }

    vector<bool> visited(n, false);
    vector<int> weight_sums(n, 0);
    int total_sum = calc_weight_sums(w, t, 0, weight_sums, visited);

    int ans = total_sum;
    for (int i = 1; i < weight_sums.size(); i++) {
        int s1 = weight_sums[i];
        int s2 = total_sum - s1;
        if (abs(s1 - s2) < ans) {
            ans = abs(s1 - s2);
        }
    }

    cout << ans << endl;

}


