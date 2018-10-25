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

    Tree(int root, const std::vector<std::pair<int,int>>& edges) :
            _lvl(0),
            _nodes(edges.size() + 1) {
        auto n = edges.size() + 1;

        // initialize node ids
        for (int i = 0; i < _nodes.size(); i++) {
            _nodes[i].id = i;
        }

        std::vector<std::vector<int>> adjacency_map(n);

        for (auto &edge : edges) {
            int a = edge.first;
            int b = edge.second;

            adjacency_map[a].push_back(b);
            adjacency_map[b].push_back(a);
        }

        std::vector<Node *> nodes;
        std::vector<bool> visited(n);

        _root = &_nodes[root];
        visited[root] = true;
        nodes.emplace_back(&_nodes[root]);

        // build the tree using BFS
        while (!nodes.empty()) {
            std::vector<Node *> tmp;
            for (auto node : nodes) {
                for (auto neighbor_id : adjacency_map[node->id]) {
                    if (!visited[neighbor_id]) {
                        _nodes[neighbor_id].parent = node;
                        node->children.push_back(&_nodes[neighbor_id]);
                        tmp.push_back(&_nodes[neighbor_id]);
                    }
                }
            }

            nodes = std::move(tmp);
            _lvl++;
        }
    }

    Node *getRoot() {
        return _root;
    }

    Node *getById(int id) {
        if (id >= 0 && id < _nodes.size()) {
            return &_nodes[id];
        } else {
            return nullptr;
        }
    }

    int getMaxLevel() {
        return _lvl;
    }

    void count() {
        _count(_root);
    }

private:
    Node *_root{nullptr};
    int _lvl;
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

// Trie

class Trie {
    const static int ALPHABET_SIZE = 26;

public:
    Trie() {
        _root = newNode();
    }

    Trie(const Trie&) = delete;

    Trie &operator=(const Trie&) = delete;

    void insert(const std::string &key) {
        auto n = _root;

        for (int i = 0; i < key.length(); i++) {
            int index = key[i] - 'a';

            if (n->children[index] == nullptr) {
                n->children[index] = newNode();
            }

            n->children_cnt++;
            n = n->children[index];
        }
    }

private:
    struct Node {
        Node *children[ALPHABET_SIZE];
        int children_cnt{0};
    };

    Node *_root{nullptr};

    Node *newNode() {
        auto n = new Node;

        for (int i = 0; i < ALPHABET_SIZE; n++) {
            n->children[i] = nullptr;
        }

        return n;
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
