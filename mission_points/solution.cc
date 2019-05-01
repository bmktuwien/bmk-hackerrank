#include <bits/stdc++.h>

using namespace std;

struct City {
    int latitude;
    int longitude;
    int height;
    int point;
};

////////////////////////////////////////////////////////////////////////////////

struct NodeY {
    int key{-1};
    long max{-1};
    long value{-1};
};

struct NodeX {
    NodeX *left{nullptr};
    NodeX *right{nullptr};
    int key{-1};
    long y{-1};
    long value{-1};
    vector<NodeY> yTree;
};

/*
NodeY *build_y_tree(const vector<pair<int,int>>& points, int l, int r) {
    if (r < l) {
        return nullptr;
    }

    int m = (l + r) / 2;

    auto *node = new NodeY();
    node->key = points[m].second;
    node->left = build_y_tree(points, l, m-1);
    node->right = build_y_tree(points, m+1, r);

    return node;
}*/

void make_bst(const vector<pair<int,int>>& in, vector<NodeY>& out, int l, int r, int i) {
    if (r < l) {
        return;
    }

    int m = (l + r) / 2;
    int k = in[m].second;

    out[i].key = k;
    make_bst(in, out, l, m-1, 2*i+1);
    make_bst(in, out, m+1, r, 2*i+2);
}


NodeX *build_range_tree(const vector<pair<int,int>>& points, int l, int r) {
    if (r < l) {
        return nullptr;
    }

    auto *node = new NodeX();

    int m = (l + r) / 2;

    vector<pair<int,int>> points_l;
    vector<pair<int,int>> points_r;

    // split the points on x
    for (auto &p : points) {
        if (p.first < m) {
            points_l.push_back(p);
        } else if (p.first > m) {
            points_r.push_back(p);
        } else {
            node->key = p.first;
            node->y = p.second;
        }
    }

    node->left = build_range_tree(points_l, l, m-1);
    node->right = build_range_tree(points_r, m+1, r);

    node->yTree.resize(points.size()*2);
    make_bst(points, node->yTree, 0, points.size()-1, 0);

    return node;
}


////////////////////////////////////////////////////////////////////////////////

inline long is_not_null(const vector<NodeY>& yTree, int idx) {
    return idx < yTree.size() && yTree[idx].key != -1;
}

inline long left_child_is_not_null(const vector<NodeY>& yTree, int idx) {
    idx = 2*idx + 1;
    return idx < yTree.size() && yTree[idx].key != -1;
}

inline long right_child_is_not_null(const vector<NodeY>& yTree, int idx) {
    idx = 2*idx + 2;
    return idx < yTree.size() && yTree[idx].key != -1;
}

long get_max_y(const vector<NodeY>& yTree, int l, int r) {
    long result = 0;

    int idx = 0;
    while (is_not_null(yTree, idx)) {
        if (yTree[idx].key < l) {
            idx = idx*2+2;
        } else if (yTree[idx].key > r) {
            idx = idx*2+1;
        } else {
            break;
        }
    }


    if (!is_not_null(yTree, idx)) {
        return result;
    }

    result = yTree[idx].value;

    int idx_l = idx*2+1;
    while (is_not_null(yTree, idx_l)) {
        if (yTree[idx_l].key >= l) {
            long tmp = yTree[idx_l].value;

            if (right_child_is_not_null(yTree, idx_l)) {
                tmp = max(tmp, yTree[idx_l*2+2].max);
            }

            if (tmp > result) {
                result = tmp;
            }
        }

        if (yTree[idx_l].key < l) {
            idx_l = idx_l*2+2;
        } else if (yTree[idx_l].key > l) {
            idx_l = idx_l*2+1;
        } else {
            break;
        }
    }

    int idx_r = idx*2+2;
    while (is_not_null(yTree, idx_r)) {
        if (yTree[idx_r].key <= r) {
            long tmp = yTree[idx_r].value;

            if (left_child_is_not_null(yTree, idx_r)) {
                tmp = max(tmp, yTree[idx_r*2+1].max);
            }

            if (tmp > result) {
                result = tmp;
            }
        }

        if (yTree[idx_r].key < r) {
            idx_r = idx_r*2+2;
        } else if (yTree[idx_r].key > r) {
            idx_r = idx_r*2+1;
        } else {
            break;
        }
    }

    return result;
}

long get_max(NodeX *node, int xl, int xr, int yl, int yr) {

    long result = 0;
    while (node != nullptr) {
        if (node->key < xl) {
            node = node->right;
        } else if (node->key > xr) {
            node = node->left;
        } else {
            break;
        }
    }

    if (node == nullptr) {
        return result;
    }

    if (yl <= node->y && node->y <= yr) {
        result = node->value;
    }

    auto *node_l = node->left;
    while (node_l != nullptr) {
        if (node_l->key >= xl) {
            long tmp = 0;
            if (node_l->right != nullptr) {
                tmp = get_max_y(node_l->right->yTree, yl, yr);
            }

            if (yl <= node_l->y && node_l->y <= yr && node_l->value > tmp) {
                tmp = node_l->value;
            }

            if (tmp > result) {
                result = tmp;
            }
        }

        if (node_l->key < xl) {
            node_l = node_l->right;
        } else if (node_l->key > xl) {
            node_l = node_l->left;
        } else {
            break;
        }
    }

    auto *node_r = node->right;
    while (node_r != nullptr ) {
        if (node_r->key <= xr) {
            long tmp = 0;
            if (node_r->left != nullptr) {
                tmp = get_max_y(node_r->left->yTree, yl, yr);
            }

            if (yl <= node_r->y && node_r->y <= yr && node_r->value > tmp) {
                tmp = node_r->value;
            }

            if (tmp > result) {
                result = tmp;
            }
        }

        if (node_r->key < xr) {
            node_r = node_r->right;
        } else if (node_r->key > xr) {
            node_r = node_r->left;
        } else {
            break;
        }
    }

    return result;
}

void updateY(vector<NodeY>& yTree, int y, long value) {
    int idx = 0;
    while (is_not_null(yTree, idx)) {
        yTree[idx].max = max(yTree[idx].max, value);

        if (y < yTree[idx].key) {
            idx = idx*2+1;
        } else if (y >  yTree[idx].key) {
            idx = idx*2+2;
        } else {
            yTree[idx].value = value;
            return;
        }
    }
}

void updateX(NodeX* node, int x, int y, long value) {
    while (node != nullptr) {
        updateY(node->yTree, y, value);

        if (x < node->key) {
            node = node->left;
        } else if (x > node->key) {
            node = node->right;
        } else {
            node->y = y;
            node->value = value;
            return;
        }
    }
}

////////////////////////////////////////////////////////////////////////////////

void solve(int n, int d_lat, int d_long, vector<City>& cities) {
    sort(cities.begin(), cities.end(), [](const City& c1, const City& c2) {
        return c1.latitude > c2.latitude;
    });
    // normalize x coordinates
    for (int i = 0; i < cities.size(); i++) {
        cities[i].latitude = i;
    }

    // sort cities by heights
    sort(cities.begin(), cities.end(), [](const City& c1, const City& c2) {
        return c1.height > c2.height;
    });

    // sort points by y coordinates
    vector<pair<int,int>> points;
    for (auto &c : cities) {
        points.emplace_back(c.latitude, c.longitude);
    }
    sort(points.begin(), points.end(), [](const pair<int,int>& p1, const pair<int,int>& p2) {
        return p1.second < p2.second;
    });

    NodeX *range_tree = build_range_tree(points, 0, points.size()-1);

    long result = 0;

    for (auto &c : cities) {
        int x1 = max(0, c.latitude - d_lat);
        int y1 = max(0, c.longitude - d_long);
        int x2 = c.latitude + d_lat;
        int y2 = c.longitude + d_long;

        long max_points = max(0L, get_max(range_tree, x1, x2, y1, y2));
        max_points += c.point;

        if (max_points > result) {
            result = max_points;
        }

        updateX(range_tree, c.latitude, c.longitude, max_points);
    }

    cout << result << endl;
}

int main(int argc, char **argv) {
    int n, d_lat, d_long;
    cin >> n >> d_lat >> d_long;

    vector<City> cities;
    for (int i = 0; i < n; i++) {
        int lat, lng, height, point;
        cin >> lat >> lng >> height >> point;
        cities.push_back({lat, lng, height, point});
    }

    solve(n, d_lat, d_long, cities);
}