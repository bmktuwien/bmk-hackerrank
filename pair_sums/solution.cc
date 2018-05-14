//
// Created by bmk on 02.05.18.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <functional>

using namespace std;

long naive_solver(const vector<int>& a) {
    if (a.size() < 2) {
        cout << "input vector size is less than 2" << endl;
        return 0;
    }

    long max = 0;

    for (int i = 0; i < a.size() - 1; i++) {
        long acc = 0;
        long sum = 0;

        for (int j = i+1; j < a.size(); j++) {
            acc += a[j-1];
            sum += acc * a[j];
            if (sum > max) {
                cout << "new max: " <<  sum << " from " << i << " to " << j << endl;
                max = sum;
            }
        }
    }

    cout << max << endl;

    return max;
}

long solver(const vector<int>& a, int l, int r) {
    if (l == r) {
        return 0;
    }

    int m = (l + r) / 2;

    vector<pair<long,long>> candidates_pos;
    vector<pair<long,long>> candidates_neg;

    long run_var = 0;
    long run_res = 0;
    for (int i = m; i >= l; i--) {
        if (i < m) {
            run_res += run_var * a[i];
        }
        run_var += a[i];

        if (run_var >= 0) {
            candidates_pos.emplace_back(run_var, run_res);
        } else {
            candidates_neg.emplace_back(run_var, run_res);
        }
    }

    sort(candidates_pos.begin(), candidates_pos.end(), greater<pair<long,long>>());
    sort(candidates_neg.begin(), candidates_neg.end());

    long x = numeric_limits<long>::min();

    vector<pair<long,long>> pos;
    for (auto p : candidates_pos) {
        if (p.second > x) {
            x = p.second;
            pos.push_back(p);
        }
    }

    x = numeric_limits<long>::min();
    vector<pair<long,long>> neg;
    for (auto p : candidates_neg) {
        if (p.second > x) {
            x = p.second;
            neg.push_back(p);
        }
    }

    long res = 0;
    run_var = 0;
    run_res = 0;
    for (int i = m+1; i <= r; i++) {
        if (i > m+1) {
            run_res += run_var * a[i];
        }
        run_var += a[i];

        if (run_var >= 0) {
            for (auto p : pos) {
                long tmp = p.second + run_res + (p.first * run_var);
                if (tmp > res) {
                    res = tmp;
                }
            }
        } else {
            for (auto p : neg) {
                long tmp = p.second + run_res + (p.first * run_var);
                if (tmp > res) {
                    res = tmp;
                }
            }
        }

    }

    //cout << "m: " << m << " res: " << res << endl;

    long res2 = solver(a, l, m);
    long res3 = solver(a, m+1,r);

    return max<long>({res,res2,res3});
}

void test() {
    random_device rnd_device;

    while (true) {
        mt19937 mersenne_engine(rnd_device());
        uniform_int_distribution<int> dist(-30, 30);

        auto gen = std::bind(dist, mersenne_engine);
        vector<int> vec(20);
        generate(begin(vec), end(vec), gen);

        cout << "input: ";
        for (auto a : vec) {
            cout << a << " ";
        }
        cout << endl;

        auto b1 = solver(vec, 0, vec.size() - 1);
        auto b2 = naive_solver(vec);

        cout << "b1: " << b1 << endl;
        cout << "b2: " << b2 << endl;

        if (b1 != b2) {
            break;
        }
    }
}

int main() {
    int n;
    cin >> n;

    vector<int> a;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        a.push_back(x);
    }

    long res = solver(a, 0, a.size()-1);
    //naive_solver(a);

    cout << res << endl;
}

