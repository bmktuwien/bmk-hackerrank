#include <bits/stdc++.h>

using namespace std;

class BITree {
public:
    explicit BITree(size_t n, int v) : _n(n), _a(n+1, v) {
    }

    void updateMax(int index, long val) {
        index = index + 1;

        while (index <= _n) {
            _a[index] = max(_a[index], val);
            index += index & (-index);
        }
    }

    long getMax(int index) {
        index = index + 1;
        long m = _a[index];

        while (index > 0) {
            m = max(m, _a[index]);
            index -= index & (-index);
        }

        return m;
    }

private:
    size_t _n;
    std::vector<long> _a;
};

int main(int argc, char **argv) {
    int n;
    cin >> n;

    vector<int> input;
    for (int i = 0; i < n; i++) {
        int k;
        cin >> k;
        input.push_back(k);
    }

    vector<int> input_copy(input);
    sort(input_copy.begin(), input_copy.end());

    unordered_map<int, int> rank_map;
    for (int i = 0; i < input_copy.size(); i++) {
        rank_map[input_copy[i]] = i;
    }

    BITree bit_left(n, 0);
    vector<long> left(n);

    for (int i = 0; i < input.size(); i++) {
        int rank = rank_map[input[i]];
        int k = n - 1 - rank;

        bit_left.updateMax(k, i+1);
        left[i] = bit_left.getMax(k-1);
    }

    BITree bit_right(n, numeric_limits<int>::min());
    vector<long> right(n);

    for (int i = input.size()-1; i >= 0; i--) {
        int rank = rank_map[input[i]];
        int k = n - 1 - rank;

        bit_right.updateMax(k, -(i+1));
        int q = bit_right.getMax(k-1);

        if (q == numeric_limits<int>::min()) {
            right[i] = 0;
        } else {
            right[i] = -q;
        }
    }

    long ans = 0;
    for (int i = 0; i < n; i++) {
        if (left[i] * right[i] > ans) {
            ans = left[i] * right[i];
        }
    }

    cout << ans << endl;
}

