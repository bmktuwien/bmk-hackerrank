#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wconversion"
#pragma clang diagnostic ignored "-Wsign-conversion"

#include <bits/stdc++.h>
#include <vector>

using namespace std;

class RootedTree {

public:
    RootedTree(int root, size_t n, const vector<vector<int>> &adjacency_map) :
            _lvl(0),
            _num_leaves(0) {
        vector<bool> visited(n, false);
        vector<int> nodes;
        nodes.push_back(root);
        visited[root] = true;

        _lvl_degrees.emplace_back(vector<int>({}));

        while (!nodes.empty()) {
            vector<int> tmp;
            vector<int> lvl_nodes;
            int leaves_cnt = 0;

            for (auto node : nodes) {
                int children_cnt = 0;

                for (auto i : adjacency_map[node]) {
                    if (!visited[i]) {
                        visited[i] = true;
                        tmp.push_back(i);
                        children_cnt++;
                    }
                }

                if (children_cnt > 0) {
                    leaves_cnt++;
                    _num_leaves++;
                }

                lvl_nodes.push_back(children_cnt);
            }

            nodes = std::move(tmp);

            if (!nodes.empty()) {
                _lvl_degrees.push_back(lvl_nodes);
            }

            _lvl_leaves_cnt.push_back(leaves_cnt);
            _lvl++;
        }
    }

    int getMaxLevel() const {
        return _lvl;
    }

    int getNumLeaves() const {
        return _num_leaves;
    }

    int getLeavesCnt(int lvl) const {
        return _lvl_leaves_cnt[lvl];
    }

    const vector<int> &getDegrees(int lvl) const {
        return _lvl_degrees[lvl];
    }

    bool isomorph(const RootedTree &t2) {
        vector<int> l1;
        vector<int> l2;

        if (getMaxLevel() != t2.getMaxLevel()) {
            return false;
        }

        if (getNumLeaves() != t2.getNumLeaves()) {
            return false;
        }

        for (int l = getMaxLevel() - 1; l >= 0; l--) {
            if (getLeavesCnt(l) != t2.getLeavesCnt(l)) {
                return false;
            }

            vector<int> labels1 = l1;
            vector<int> labels2 = l2;

            sort(labels1.begin(), labels1.end());
            sort(labels2.begin(), labels2.end());

            if (labels1 != labels2) {
                return false;
            }

            vector<int> tmp1;
            vector<int> tmp2;
            map<vector<int>, int> label_integer_map;

            auto &degrees_1 = getDegrees(l);
            int idx = 0;
            int label_integer = 1;

            for (auto cnt : degrees_1) {
                if (cnt > 0) {
                    vector<int> label;
                    while (cnt--) {
                        if (l1.empty()) {
                            label.push_back(1);
                        } else {
                            label.push_back(l1[idx]);
                            idx++;
                        }
                    }

                    sort(label.begin(), label.end());

                    auto it = label_integer_map.find(label);
                    if (it != label_integer_map.end()) {
                        tmp1.push_back(it->second);
                    } else {
                        tmp1.push_back(label_integer);
                        label_integer_map[label] = label_integer;
                        label_integer++;
                    }

                } else {
                    tmp1.emplace_back(0);
                }
            }

            auto &degrees_2 = t2.getDegrees(l);
            idx = 0;
            for (auto cnt : degrees_2) {
                if (cnt > 0) {
                    vector<int> label;
                    while (cnt--) {
                        if (l2.empty()) {
                            label.push_back(1);
                        } else {
                            label.push_back(l2[idx]);
                            idx++;
                        }
                    }

                    sort(label.begin(), label.end());

                    auto it = label_integer_map.find(label);
                    if (it != label_integer_map.end()) {
                        tmp2.push_back(it->second);
                    } else {
                        return false;
                    }
                } else {
                    tmp2.emplace_back(0);
                }
            }

            l1 = std::move(tmp1);
            l2 = std::move(tmp2);
        }

        return true;
    }

private:
    int _lvl;
    int _num_leaves;
    vector<int> _lvl_leaves_cnt;
    vector<vector<int>> _lvl_degrees;
};

unordered_map<int, vector<RootedTree>> cache;

class SubTree {
public:
    SubTree(int v, int r, int n, const vector<vector<int>> &adjacency_map) :
            _n(n),
            _root(v),
            _lvl(0),
            _cnt(1),
            _max_leaf(-1),
            _parent_map(n, -1),
            _children_map(n) {
        vector<bool> visited(_n, false);
        vector<int> nodes;

        nodes.push_back(v);
        visited[v] = true;

        int max_level = 0;

        while (_lvl <= r && !nodes.empty()) {
            vector<int> tmp;

            for (auto node : nodes) {
                if (_lvl > max_level) {
                    max_level = _lvl;
                    _max_leaf = node;
                }

                if (_lvl < r) {
                    for (auto i : adjacency_map[node]) {
                        if (!visited[i]) {
                            visited[i] = true;
                            tmp.push_back(i);
                            _edges.emplace_back(node, i);
                            _cnt++;

                            _parent_map[i] = node;
                            _children_map[node].push_back(i);
                        }
                    }
                }

            }

            nodes = std::move(tmp);
            _lvl++;
        }
    }

    int getMaxLevel() const {
        return _lvl;
    }

    int getCnt() const {
        return _cnt;
    }

    int getRoot() const {
        return _root;
    }

    const vector<pair<int, int>> &getEdges() const {
        return _edges;
    }

    vector<int> getCenters() {
        if (_centers.empty()) {
            vector<bool> visited(_n, false);
            int d = calcDiameter(_max_leaf, visited, _parent_map, _children_map);

            vector<int> medians;
            medians.push_back(d / 2);
            if (d % 2 != 0) {
                medians.push_back(d / 2 + 1);
            }

            for (auto median : medians) {
                int center = _max_leaf;
                while (median--) {
                    assert(_parent_map[center] != -1);
                    center = _parent_map[center];
                }

                _centers.push_back(center);
            }
        }

        return _centers;
    }

    bool isomorph(SubTree &t2) {
        if (getCenters().size() != t2.getCenters().size()) {
            return false;
        }

        vector<vector<int>> adjacency_map_t1(_n);
        for (auto &edge : getEdges()) {
            adjacency_map_t1[edge.first].push_back(edge.second);
            adjacency_map_t1[edge.second].push_back(edge.first);
        }

        RootedTree t1_rooted(getCenters()[0], _n, adjacency_map_t1);

        // cache rooted trees of t2
        if (cache.find(t2.getRoot()) == cache.end()) {
            vector<vector<int>> adjacency_map_t2(_n);
            for (auto edge : t2.getEdges()) {
                adjacency_map_t2[edge.first].push_back(edge.second);
                adjacency_map_t2[edge.second].push_back(edge.first);
            }

            for (auto center : t2.getCenters()) {
                RootedTree t2_rooted(center, _n, adjacency_map_t2);
                cache[t2.getRoot()].push_back(t2_rooted);
            }
        }

        for (auto &rt : cache[t2.getRoot()]) {
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
    int _root;
    int _max_leaf;
    vector<int> _parent_map;
    vector<vector<int>> _children_map;
    vector<pair<int, int>> _edges;
    vector<int> _centers;

    int calcDiameter(int v, vector<bool> &visited,
                     const vector<int> &parent_map,
                     const vector<vector<int>> &children_map) const {
        int d = 0;
        visited[v] = true;

        if (parent_map[v] != -1) {
            if (!visited[parent_map[v]]) {
                int t = calcDiameter(parent_map[v], visited, parent_map,
                                     children_map) + 1;
                if (t > d) {
                    d = t;
                }
            }
        }

        for (auto child : children_map[v]) {
            if (!visited[child]) {
                int t = calcDiameter(child, visited, parent_map, children_map) + 1;
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
    bool whole_tree_encountered = false;

    SubTree tree(0, n, n, adjacency_map);
    auto centers = tree.getCenters();
    SubTree centered_tree(centers[0], n, n, adjacency_map);

    vector<bool> skip(n, false);

    // try to mark subtrees which consist of all nodes as skippable
    if (centered_tree.getMaxLevel() < r) {
        int center = centers[0];
        vector<bool> visited(n, false);
        vector<int> nodes;

        int lvl = 0;
        whole_tree_encountered = true;
        ans++;
        nodes.push_back(center);
        skip[center] = true;

        int r2 = r - centered_tree.getMaxLevel();
        while (lvl <= r2 && !nodes.empty()) {
            vector<int> tmp;

            for (auto node : nodes) {
                if (lvl < r2) {
                    for (auto i : adjacency_map[node]) {
                        if (!skip[i]) {
                            skip[node] = true;
                            tmp.push_back(i);
                        }
                    }
                }
            }

            nodes = std::move(tmp);
            lvl++;
        }
    }

    // generated all subtrees and count only non-isomorphic subtrees
    for (int i = 0; i < n; i++) {
        if (skip[i]) {
            continue;
        }

        SubTree sub_tree(i, r, n, adjacency_map);

        int cnt = sub_tree.getCnt();
        if (cnt == n) {
            if (!whole_tree_encountered) {
                ans++;
                whole_tree_encountered = true;
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