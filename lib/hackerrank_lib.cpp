#include "hackerrank_lib.h"

#include <vector>
#include <iostream>

namespace hackerrank_lib {

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

class BITree {
public:
    explicit BITree(size_t n) : _n(n) {
        _a.resize(n+1);
    }

    void update(int index, long val) {
        index = index + 1;

        while (index <= _n) {
            _a[index] += val;
            index += index & (-index);
        }
    }

    long getSum(int index) {
        long sum = 0;
        index = index + 1;

        while (index>0) {
            sum += _a[index];
            index -= index & (-index);
        }

        return sum;
    }

private:
    size_t _n;
    std::vector<long> _a;
};

////////////////////////////////////////////////////////////////////////////////

class Tree {
public:
    struct Node {
        int id{-1};
        Node *parent{nullptr};
        int cnt{-1};
        std::vector<Node *> children;
    };

    explicit Tree(const std::vector<std::pair<int,int>>& edges) {
        _nodes.resize(edges.size() + 1);

        for (int i = 0; i < _nodes.size(); i++) {
            _nodes[i].id = i;
        }

        for (auto &edge : edges) {
            int xid = edge.first - 1;
            int yid = edge.second - 1;

            if (_nodes[yid].parent != nullptr) {
                std::vector<Node *> stack;

                Node *p = &_nodes[yid];
                while (p != nullptr) {
                    stack.push_back(p);
                    p = p->parent;
                }

                while (stack.size() > 1) {
                    p = stack.back();
                    stack.pop_back();
                    p->parent = stack.back();
                }

            }

            _nodes[yid].parent = &_nodes[xid];
        }

        for (auto &node : _nodes) {
            if (node.parent != nullptr) {
                node.parent->children.push_back(&_nodes[node.id]);
            } else {
                _root = &_nodes[node.id];
            }
        }
    }

    void count_nodes() {
        _count(_root);
    }

    Node *getRoot() {
        return _root;
    }

private:
    Node *_root{nullptr};
    std::vector<Node> _nodes;

    int _count(Node *node) {
        int c = 1;

        for (auto child : node->children) {
            c += _count(child);
        }

        node->cnt = c;
        return c;
    }
};

////////////////////////////////////////////////////////////////////////////////

// ATTENTION: input array must be sorted!
long sum_diff_of_pairs(const std::vector<int>& a) {
    long sum = 0;
    auto n = a.size();

    for (auto i = n - 1; i >= 0; i--) {
        sum += i*a[i] - (n-1-i)*a[i];
    }

    return sum;
}

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

} // namespace hackerrank_lib
