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

    long sum_max_l = 0;
    long res_max_l = 0;

    long sum_min_l = 0;
    long res_min_l = 0;

    long run_var = 0;
    long run_res = 0;
    for (int i = m; i >= l; i--) {
        if (i < m) {
            run_res += run_var * a[i];
        }
        run_var += a[i];

        if (run_var > sum_max_l) {
            sum_max_l = run_var;

            if (i < m) {
                res_max_l = run_res;
            }
        }

        if (run_var < sum_min_l) {
            sum_min_l = run_var;

            if (i < m) {
                res_min_l = run_res;
            }
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

        long tmp = res_max_l + run_res + (sum_max_l * run_var);
        long tmp2 = res_min_l + run_res + (sum_min_l * run_var);

        if (tmp > res) {
            res = tmp;
        }

        if (tmp2 > res) {
            res = tmp2;
        }
    }

    long sum_max_r = 0;
    long res_max_r = 0;

    long sum_min_r = 0;
    long res_min_r = 0;

    run_var = 0;
    run_res = 0;
    for (int i = m+1; i <= r; i++) {
        if (i > m+1) {
            run_res += run_var * a[i];
        }
        run_var += a[i];

        if (run_var > sum_max_r) {
            sum_max_r = run_var;

            if (i > m+1) {
                res_max_r = run_res;
            }
        }

        if (run_var < sum_min_r) {
            sum_min_r = run_var;

            if (i > m+1) {
                res_min_r = run_res;
            }
        }
    }

    run_var = 0;
    run_res = 0;
    for (int i = m; i >= l; i--) {
        if (i < m) {
            run_res += run_var * a[i];
        }
        run_var += a[i];

        long tmp = res_max_r + run_res + (sum_max_r * run_var);
        long tmp2 = res_min_r + run_res + (sum_min_r * run_var);

        if (tmp > res) {
            res = tmp;
        }

        if (tmp2 > res) {
            res = tmp2;
        }
    }

    cout << "m: " << m << " res: " << res << endl;

    long res2 = solver(a, l, m);
    long res3 = solver(a, m+1,r);

    return max<long>({res,res2,res3});
}

int main() {

    random_device rnd_device;
    // Specify the engine and distribution.

    while (true) {
        mt19937 mersenne_engine(rnd_device());
        uniform_int_distribution<int> dist(-10, 10);

        auto gen = std::bind(dist, mersenne_engine);
        vector<int> vec(6);
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


    /*int n;
    cin >> n;

    vector<int> a;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        a.push_back(x);
    }

    long res = solver(a, 0, a.size()-1);
    naive_solver(a);

    cout << "res: " << res << endl;*/

}

