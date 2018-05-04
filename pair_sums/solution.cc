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

    long acc = 0;
    long max_ending_here = 0;
    long max_so_far = 0;

    for (int i = 1; i < a.size(); i++) {
        acc += a[i-1];

        if (max_ending_here + a[i]*acc < a[i]*a[i-1]) {
            acc = a[i-1];
            max_ending_here = a[i]*a[i-1];
        } else {
            max_ending_here += a[i]*acc;
        }

        max_so_far = max<long>(max_ending_here, max_so_far);
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
    //naive_solver(a);
}

