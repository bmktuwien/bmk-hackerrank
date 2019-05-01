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
    NodeY *left{nullptr};
    NodeY *right{nullptr};
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
    NodeY *yTree{nullptr};
};

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
    node->yTree = build_y_tree(points, 0, points.size()-1);

    return node;
}


////////////////////////////////////////////////////////////////////////////////

long get_max_y(NodeY *node, int l, int r) {
    long result = 0;
    while (node != nullptr) {
        if (node->key < l) {
            node = node->right;
        } else if (node->key > r) {
            node = node->left;
        } else {
            break;
        }
    }

    if (node == nullptr) {
        return result;
    }

    result = node->value;

    auto *node_l = node->left;
    while (node_l != nullptr) {
        if (node_l->key >= l) {
            long tmp = max(node_l->value, node_l->right != nullptr ? node_l->right->max : 0L);

            if (tmp > result) {
                result = tmp;
            }
        }

        if (node_l->key < l) {
            node_l = node_l->right;
        } else if (node_l->key > l) {
            node_l = node_l->left;
        } else {
            break;
        }
    }

    auto *node_r = node->right;
    while (node_r != nullptr) {
        if (node_r->key <= r) {
            long tmp = max(node_r->value, node_r->left != nullptr ? node_r->left->max : 0L);

            if (tmp > result) {
                result = tmp;
            }
        }

        if (node_r->key < r) {
            node_r = node_r->right;
        } else if (node_r->key > r) {
            node_r = node_r->left;
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
            auto ptr = node_l->right != nullptr ? node_l->right->yTree : nullptr;
            long tmp = get_max_y(ptr, yl, yr);
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
            auto ptr = node_r->left != nullptr ? node_r->left->yTree : nullptr;
            long tmp = get_max_y(ptr, yl, yr);
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

void updateY(NodeY* node, int y, long value) {
    while (node != nullptr) {
        node->max = max(node->max, value);

        if (y < node->key) {
            node = node->left;
        } else if (y > node->key) {
            node = node->right;
        } else {
            node->value = value;
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

/*struct Entry {
    int latitude;
    int longitude;
    long max_points;
};*/


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

    //vector<Entry> acc;

    for (auto &c : cities) {
        int x1 = max(0, c.latitude - d_lat);
        int y1 = max(0, c.longitude - d_long);
        int x2 = c.latitude + d_lat;
        int y2 = c.longitude + d_long;

        /*long max_points2 = 0;
        for (const Entry& e : acc) {
            if ((abs(e.latitude-c.latitude) <= d_lat) &&
                (abs(e.longitude-c.longitude) <= d_long) &&
                (e.max_points > max_points2)) {
                max_points2 = e.max_points;
            }
        }


        cout << "x1=" << x1 << " y1=" << y1 << " x2=" << x2 << " y2=" << y2 << " x=" << c.latitude << " y=" << c.longitude << endl;
        long max_points = max(0L, get_max(range_tree, x1, x2, y1, y2));
        cout << "maxpoints=" << max_points << endl;
        cout << "maxpoints2=" << max_points2 << endl;
        cout << "c=" << max_points+c.point << endl;
        cout << "-----------------------------------" << endl;

        if (max_points != max_points2) {
            cout << "fuck!" << endl;
            get_max(range_tree, x1, x2, y1, y2);
            return;
        }*/

        long max_points = max(0L, get_max(range_tree, x1, x2, y1, y2));
        max_points += c.point;

        if (max_points > result) {
            result = max_points;
        }

        //acc.push_back({c.latitude, c.longitude, max_points+c.point});
        updateX(range_tree, c.latitude, c.longitude, max_points);

    }

    cout << result << endl;
}

int main(int argc, char **argv) {
    //std::ifstream is("tests/input05.txt");

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