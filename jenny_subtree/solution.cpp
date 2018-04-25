#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wconversion"
#pragma clang diagnostic ignored "-Wsign-conversion"

#include <bits/stdc++.h>
#include <vector>

using namespace std;

class RootedTree {

public:
    RootedTree(int root, size_t n, vector<vector<int>> &adjacency_map) :
            _cnt(1),
            _lvl(0),
            _num_leaves(0) {
        vector<bool> visited(n, false);
        vector<int> nodes;
        nodes.push_back(root);
        visited[root] = true;

        _lvl_children_cnt.emplace_back(vector<int>({}));

        while (!nodes.empty()) {
            vector<int> tmp;
            vector<int> lvl_nodes;
            int leaves_cnt = 0;

            for (auto n1 : nodes) {
                int children_cnt = 0;

                for (auto i : adjacency_map[n1]) {
                    if (!visited[i]) {
                        visited[i] = true;
                        tmp.push_back(i);
                        children_cnt++;
                        _cnt++;
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
                _lvl_children_cnt.push_back(lvl_nodes);
            }

            _lvl_leaves_cnt.push_back(leaves_cnt);
            _lvl++;
        }
    }

    int getMaxLevel() const {
        return _lvl_children_cnt.size();
    }

    int getCnt() const {
        return _cnt;
    }

    int getNumLeaves() const {
        return _num_leaves;
    }

    int getLeavesCnt(int lvl) const {
        return _lvl_leaves_cnt[lvl];
    }

    const vector<int> &getChildrenCnt(int lvl) const {
        return _lvl_children_cnt[lvl];
    }

    bool isomorph(const RootedTree &t2) {
        vector<vector<int>> l1;
        vector<vector<int>> l2;

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

            vector<vector<int>> labels1;
            for (auto &v : l1) {
                sort(v.begin(), v.end());
                labels1.push_back(v);
            }

            vector<vector<int>> labels2;
            for (auto &v : l2) {
                sort(v.begin(), v.end());
                labels2.push_back(v);
            }

            sort(labels1.begin(), labels1.end());
            sort(labels2.begin(), labels2.end());

            if (labels1 != labels2) {
                return false;
            }

            auto x = unique(labels1.begin(), labels1.end());

            vector<vector<int>> tmp1;
            vector<vector<int>> tmp2;

            map<vector<int>, int> label_integer_map;
            int idx = 1;
            for (auto it = labels1.begin(); it != x; it++) {
                label_integer_map[*it] = idx;
                idx++;
            }

            auto &children_cnts_1 = getChildrenCnt(l);
            idx = 0;
            for (auto cnt : children_cnts_1) {
                if (cnt > 0) {
                    vector<int> label;
                    while (cnt--) {
                        if (l1.empty()) {
                            label.push_back(1);
                        } else {
                            label.push_back(label_integer_map[l1[idx]]);
                            idx++;
                        }

                    }
                    tmp1.push_back(label);
                } else {
                    tmp1.emplace_back(vector<int>({0}));
                }
            }

            auto &children_cnts_2 = t2.getChildrenCnt(l);
            idx = 0;
            for (auto cnt : children_cnts_2) {
                if (cnt > 0) {
                    vector<int> label;
                    while (cnt--) {
                        if (l2.empty()) {
                            label.push_back(1);
                        } else {
                            label.push_back(label_integer_map[l2[idx]]);
                            idx++;
                        }
                    }
                    tmp2.push_back(label);
                } else {
                    tmp2.emplace_back(vector<int>({0}));
                }
            }

            l1 = std::move(tmp1);
            l2 = std::move(tmp2);
        }

        return true;
    }

private:
    int _lvl;
    int _cnt;
    int _num_leaves;
    vector<int> _lvl_leaves_cnt;
    vector<vector<int>> _lvl_children_cnt;
};

unordered_map<int, vector<RootedTree>> cache;

class SubTree {
public:
    SubTree(int v, int r, int n, const vector<vector<int>> &adjacency_map) :
            _n(n),
            _v(v),
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

    int getV() const {
        return _v;
    }

    const vector<pair<int, int>> &getEdges() const {
        return _edges;
    }

    vector<int> getCenters() {
        if (_centers.empty()) {
            vector<bool> visited(_n, false);
            int d = findDiameter(_max_leaf, visited, _parent_map, _children_map);

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
    int _max_leaf;
    vector<int> _parent_map;
    vector<vector<int>> _children_map;
    vector<pair<int, int>> _edges;
    vector<int> _centers;

    int findDiameter(int v, vector<bool> &visited, const vector<int> &parent_map,
                     const vector<vector<int>> &children_map) const {
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