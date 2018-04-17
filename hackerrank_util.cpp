#include "hackerrank_util.h"

#include <vector>
#include <iostream>

namespace hackerrank_util {

class DUS {
public:
    explicit DUS(size_t n) {
        _rank.resize(n, 0);
        _parent.resize(n, 0);;
        makeSet();
    }

    void makeSet() {
        for (int i=0; i<_parent.size(); i++) {
            _parent[i] = i;
        }
    }

    int find(int x) {
        if (_parent[x]!=x) {
            _parent[x] = find(_parent[x]);
        }

        return _parent[x];
    }

    void union_(int x, int y) {
        int xRoot = find(x);
        int yRoot = find(y);

        if (xRoot == yRoot) {
            return;
        }

        if (_rank[xRoot] < _rank[yRoot]) {
            _parent[xRoot] = yRoot;
        } else if (_rank[yRoot] < _rank[xRoot]) {
            _parent[yRoot] = xRoot;
        } else {
            _parent[yRoot] = xRoot;
            _rank[xRoot] = _rank[xRoot] + 1;
        }
    }

private:
    std::vector<int> _rank;
    std::vector<int> _parent;
};

////////////////////////////////////////////////////////////////////////////////

long n_choose_k(int n, int k) {
    if (n < k) {
        return 0;
    }

    long res = 1;

    if (k > n - k) {
        k = n - k;
    }

    for (int i = 0; i < k; ++i) {
        res *= (n - i);
        res /= (i + 1);
    }

    return res;
}

} // namespace hackerrank_util
