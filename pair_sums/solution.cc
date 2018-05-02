//
// Created by bmk on 02.05.18.
//

#include <iostream>
#include <vector>

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

int main() {
    int n;
    cin >> n;

    vector<int> a;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        a.push_back(x);
    }

    naive_solver(a);
}

