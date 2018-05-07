//
// Created by bmk on 02.05.18.
//

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void naive_solver(const vector<int>& a) {
    if (a.size() < 2) {
        cout << "input vector size is less than 2" << endl;
        return;
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
}

void solver(const vector<int>& a) {
    if (a.size() < 2) {
        cout << "input vector size is less than 2" << endl;
        return;
    }

    long max_ending_here = a[0];
    long min_ending_here = a[0];

    long sum1 = 0;
    long sum2 = 0;q
    long max_so_far = 0;

    for (int i = 1; i < a.size(); i++) {
        if (max_ending_here + a[i] > a[i]) {
            sum1 += max_ending_here * a[i];
            cout << "max_sum[" << i << "]: " << sum1 << endl;
            if (max_so_far < sum1) {
                max_so_far = sum1;
            }
        } else {
            cout << "******************************" << endl;
            sum1 = 0;
        }

        if (min_ending_here + a[i] < a[i]) {
            sum2 += min_ending_here * a[i];
            cout << "min_sum[" << i << "]: " << sum2 << endl;
            if (max_so_far < sum2) {
                max_so_far = sum2;
            }
        } else {
            cout << "-------------------------------" << endl;
            sum2 = 0;
        }

        max_ending_here = max<long>(a[i], max_ending_here + a[i]);
        min_ending_here = min<long>(a[i], min_ending_here + a[i]);
    }

    cout << max_so_far << endl;
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

    solver(a);
    naive_solver(a);

    long sum = 0;
    for (int i = 333; i <= 1131; i++) {
        sum += a[i];
    }
    cout << "shit1: " << sum << endl;


    sum = 0;
    for (int i = 430; i <= 1131; i++) {
        sum += a[i];
    }
    cout << "shit2: " << sum << endl;
}

