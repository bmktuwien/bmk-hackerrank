#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wconversion"
#pragma clang diagnostic ignored "-Wsign-conversion"

#include <bits/stdc++.h>
#include <vector>
#include <unordered_map>

using namespace std;

class RootedTree {

    struct Node {
        int id{-1};
        Node *parent{nullptr};
        std::vector<Node *> children;
    };

public:
    RootedTree(int root, size_t n, vector<vector<int>> &adjacency_map) :
            _cnt(1),
            _lvl(0),
            _num_leaves(0) {
        vector<bool> visited(n, false);

        vector<Node *> nodes;
        _root = new Node();
        _root->id = root;
        nodes.push_back(_root);
        visited[root] = true;

        while (!nodes.empty()) {
            vector<Node *> tmp;
            vector<Node *> leaves;
            for (auto n1 : nodes) {
                vector<Node *> children;

                for (auto i : adjacency_map[n1->id]) {
                    if (!visited[i]) {
                        visited[i] = true;
                        auto n2 = new Node();
                        n2->id = i;
                        n2->parent = n1;
                        children.push_back(n2);
                        tmp.push_back(n2);
                        _cnt++;
                    }
                }

                n1->children = std::move(children);

                if (n1->children.empty()) {
                    _num_leaves++;
                    leaves.push_back(n1);
                }
            }

            nodes = std::move(tmp);

            _lvl_leaves.push_back(leaves);
            _lvl++;
        }
    }

    Node *getRoot() {
        return _root;
    }

    int getMaxLevel() const {
        return _lvl_leaves.size();
    }

    int getCnt() const {
        return _cnt;
    }

    int getNumLeaves() const {
        return _num_leaves;
    }

    vector<Node *> getLeaves(int lvl) const {
        return _lvl_leaves[lvl];
    }

    bool isomorph(const RootedTree &t2) {
        unordered_map<Node *, vector<int>> l1;
        unordered_map<Node *, vector<int>> l2;

        if (getMaxLevel() != t2.getMaxLevel()) {
            return false;
        }

        if (getNumLeaves() != t2.getNumLeaves()) {
            return false;
        }

        for (int l = getMaxLevel() - 1; l >= 0; l--) {
            auto leaves1 = getLeaves(l);
            auto leaves2 = t2.getLeaves(l);

            if (leaves1.size() != leaves2.size()) {
                return false;
            }

            vector<vector<int>> labels1;
            vector<vector<int>> labels2;

            for (auto &p : l1) {
                sort(p.second.begin(), p.second.end());
                labels1.push_back(p.second);
            }

            for (auto &p : l2) {
                sort(p.second.begin(), p.second.end());
                labels2.push_back(p.second);
            }

            sort(labels1.begin(), labels1.end());
            sort(labels2.begin(), labels2.end());

            cout << "level " << l << endl;
            cout << "nodes1: ";
            for (auto p : l1) {
                cout << p.first->id << " ";
            }
            for (auto leaf : leaves1) {
                cout << leaf->id << " ";
            }
            cout << endl;
            cout << "labels1: ";
            for (auto label : labels1) {
                cout << "[";
                for (auto i : label) {
                    cout << i << " ";
                }
                cout << "] ";
            }
            cout << endl;

            cout << "nodes2: ";
            for (auto p : l2) {
                cout << p.first->id << " ";
            }
            for (auto leaf : leaves2) {
                cout << leaf->id << " ";
            }
            cout << endl;
            cout << "labels2: ";
            for (auto label : labels2) {
                cout << "[";
                for (auto i : label) {
                    cout << i << " ";
                }
                cout << "] ";
            }
            cout << endl;


            if (labels1 != labels2) {
                return false;
            }

            unique(labels1.begin(), labels1.end());

            unordered_map<Node *, vector<int>> tmp1;
            unordered_map<Node *, vector<int>> tmp2;

            for (auto &p : l1) {
                if (p.first->parent != nullptr) {
                    int number = 0;

                    for (int j = 0; j < labels1.size(); j++) {
                        if (labels1[j] == p.second) {
                            number = j;
                        }
                    }

                    tmp1[p.first->parent].push_back(number);
                }
            }
            for (auto leaf : leaves1) {
                tmp1[leaf].push_back({0});
            }

            for (auto &p : l2) {
                if (p.first->parent != nullptr) {
                    int number = 0;

                    for (int j = 0; j < labels1.size(); j++) {
                        if (labels1[j] == p.second) {
                            number = j;
                        }
                    }

                    tmp2[p.first->parent].push_back(number);
                }
            }
            for (auto leaf : leaves2) {
                tmp2[leaf].push_back({0});
            }

            l1 = std::move(tmp1);
            l2 = std::move(tmp2);
        }

        return true;
    }

private:
    Node *_root{nullptr};
    int _lvl;
    int _cnt;
    int _num_leaves;
    vector<vector<Node *>> _lvl_leaves;
};

unordered_map<int, vector<RootedTree>> cache;

class SubTree {
public:
    SubTree(int v, int r, int n, const vector<vector<int>> &adjacency_map) :
            _n(n),
            _v(v),
            _lvl(0),
            _cnt(1) {

        vector<int> parent_map(n, -1);
        vector<vector<int>> children_map(_n);

        vector<bool> visited(_n, false);
        vector<int> nodes;

        nodes.push_back(v);
        visited[v] = true;

        int max_level = 0;
        int max_leaf = v;

        while (_lvl <= r && !nodes.empty()) {
            vector<int> tmp;

            for (auto node : nodes) {
                if (_lvl > max_level) {
                    max_level = _lvl;
                    max_leaf = node;
                }

                if (_lvl < r) {
                    for (auto i : adjacency_map[node]) {
                        if (!visited[i]) {
                            visited[i] = true;
                            tmp.push_back(i);
                            _edges.emplace_back(node, i);
                            _cnt++;

                            parent_map[i] = node;
                            children_map[node].push_back(i);
                        }
                    }
                }

            }

            nodes = std::move(tmp);
            _lvl++;
        }

        // FIXME: hacky optimization
        if (_cnt == _n) {
            return;
        }

        visited.clear();
        visited.resize(_n, false);
        int d = findDiameter(max_leaf, visited, parent_map, children_map);

        vector<int> medians;
        medians.push_back(d / 2);
        if (d % 2 != 0) {
            medians.push_back(d / 2 + 1);
        }

        for (auto median : medians) {
            int center = max_leaf;
            while (median--) {
                assert(parent_map[center] != -1);
                center = parent_map[center];
            }
            _centers.push_back(center);
        }
    }

    int getMaxLevel() const {
        return _lvl;
    }

    int getCnt() const {
        return _cnt;
    }

    int getV() const {
        return _v;
    }

    const vector<pair<int, int>> &getEdges() const {
        return _edges;
    }

    vector<int> getCenters() const {
        return _centers;
    }

    bool isomorph(const SubTree &t2) {
        if (getCenters().size() != t2.getCenters().size()) {
            return false;
        }

        vector<vector<int>> adjacency_map_t1(_n);
        for (auto &edge : getEdges()) {
            adjacency_map_t1[edge.first].push_back(edge.second);
            adjacency_map_t1[edge.second].push_back(edge.first);
        }

        RootedTree t1_rooted(getCenters()[0], _n, adjacency_map_t1);

        if (cache.find(t2.getV()) == cache.end()) {
            vector<vector<int>> adjacency_map_t2(_n);
            for (auto edge : t2.getEdges()) {
                adjacency_map_t2[edge.first].push_back(edge.second);
                adjacency_map_t2[edge.second].push_back(edge.first);
            }

            for (auto center : t2.getCenters()) {
                RootedTree t2_rooted(center, _n, adjacency_map_t2);
                cache[t2.getV()].push_back(t2_rooted);
            }
        }

        for (auto &rt : cache[t2.getV()]) {
            if (t1_rooted.isomorph(rt)) {
                return true;
            }
        }

        return false;
    }

private:
    int _n;
    int _lvl;
    int _cnt;
    int _v;
    vector<pair<int, int>> _edges;
    vector<int> _centers;

    int findDiameter(int v, vector<bool> &visited, const vector<int> &parent_map,
                     const vector<vector<int>> &children_map) {
        int d = 0;
        visited[v] = true;

        if (parent_map[v] != -1) {
            if (!visited[parent_map[v]]) {
                int t = findDiameter(parent_map[v], visited, parent_map,
                                     children_map) + 1;
                if (t > d) {
                    d = t;
                }
            }
        }

        for (auto child : children_map[v]) {
            if (!visited[child]) {
                int t = findDiameter(child, visited, parent_map, children_map) + 1;
                if (t > d) {
                    d = t;
                }
            }
        }

        return d;
    }
};


int main() {
    int n, r;
    cin >> n >> r;

    vector<vector<int>> adjacency_map(n);
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        a--;
        b--;

        adjacency_map[a].push_back(b);
        adjacency_map[b].push_back(a);
    }

    unordered_map<int, vector<SubTree>> subtree_map;

    int ans = 0;
    bool whole_tree = false;

    for (int i = 0; i < n; i++) {
        SubTree sub_tree(i, r, n, adjacency_map);

        int cnt = sub_tree.getCnt();
        if (cnt == n) {
            if (!whole_tree) {
                ans++;
                whole_tree = true;
            }
            continue;
        }

        if (subtree_map.find(cnt) != subtree_map.end()) {
            bool isomorph = false;
            for (auto &t : subtree_map[cnt]) {
                if (sub_tree.isomorph(t)) {
                    isomorph = true;
                    break;
                }
            }

            if (!isomorph) {
                subtree_map[cnt].push_back(std::move(sub_tree));
                ans++;
            }
        } else {
            subtree_map[cnt].push_back(std::move(sub_tree));
            ans++;
        }
    }

    cout << ans << endl;

    return 0;
}

#pragma clang diagnostic pop