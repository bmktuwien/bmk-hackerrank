//
// Created by bmk on 28.05.18.
//

#include <bits/stdc++.h>

using namespace std;

long solve(vector<long>& v, long k, int l, int h) {
    if (l == h) {
        return  v[l] % k;
    }

    int m = (l + h) / 2;

    long m1 = solve(v, k, l, m);
    long m2 = solve(v, k, m+1, h);

    long m3 = 0;
    long sum = 0;
    set<long> s;
    for (int i = m; i >= l; i--) {
        sum += (v[i] % k);
        sum = sum % k;

        if (sum > m3) {
            m3 = sum;
        }
        s.insert(sum);
    }


    sum = 0;
    for (int i = m+1; i <= h; i++) {
        sum += (v[i] % k);
        sum = sum % k;

        auto d = k - sum;
        auto it = s.lower_bound(d);
        if (it != s.begin()) {
            it--;
            if ((sum + *it) % k > m3) {
                m3 = (sum + *it) % k;
            }
        }
    }

    return max({m1,m2,m3});
}

int main() {
    int q;
    cin >> q;

    while(q--) {
        int n, m;
        cin >> n >> m;

        vector<long> v;
        for (int i = 0; i < n; i++) {
            long j;
            cin >> j;
            v.push_back(j);
        }

        auto ans = solve(v, m, 0, n-1);
        cout << ans << endl;

    }

    return 0;
}