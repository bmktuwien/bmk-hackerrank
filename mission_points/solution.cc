#include <bits/stdc++.h>

using namespace std;

struct City {
    int latitude;
    int longitude;
    int height;
    int point;
};

struct NodeY {
    int key{-1};
    long max{-1};
    long value{-1};
};

struct NodeX {
    int key{-1};
    long y{-1};
    long value{-1};
    vector<NodeY> yTree;
};

////////////////////////////////////////////////////////////////////////////////

void make_y_bst(const vector<pair<int, int>> &in, vector<NodeY> &out,
                int l, int r, int i) {
    if (r < l) {
        return;
    }

    int m = (l + r) / 2;
    int k = in[m].second;

    out[i].key = k;
    make_y_bst(in, out, l, m - 1, 2*i + 1);
    make_y_bst(in, out, m + 1, r, 2*i + 2);
}


void make_x_bst(const vector<pair<int,int>>& in, vector<NodeX> &out,
                int l, int r, int i) {
    if (r < l) {
        return;
    }

    int m = (l + r) / 2;

    vector<pair<int,int>> points_l;
    vector<pair<int,int>> points_r;

    // split the points on x
    for (auto &p : in) {
        if (p.first < m) {
            points_l.push_back(p);
        } else if (p.first > m) {
            points_r.push_back(p);
        } else {
            out[i].key = p.first;
            out[i].y = p.second;
        }
    }

    if (i > 0) {
        out[i].yTree.resize(in.size()*2);
        make_y_bst(in, out[i].yTree, 0, in.size() - 1, 0);
    }

    make_x_bst(points_l, out, l, m-1, 2*i + 1);
    make_x_bst(points_r, out, m+1, r, 2*i + 2);
}


////////////////////////////////////////////////////////////////////////////////

template<typename T>
inline bool is_not_null(const vector<T> &t, int idx) {
    return idx < t.size() && t[idx].key != -1;
}

template<typename T>
inline bool left_child_is_not_null(const vector<T> &t, int idx) {
    idx = 2*idx + 1;
    return idx < t.size() && t[idx].key != -1;
}

template<typename T>
inline bool right_child_is_not_null(const vector<T> &t, int idx) {
    idx = 2*idx + 2;
    return idx < t.size() && t[idx].key != -1;
}

long get_max_y(const vector<NodeY>& yTree, int l, int r, long best_so_far) {
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

    if (yTree[idx].max == -1 || yTree[idx].max <= best_so_far) {
        return result;
    }

    result = yTree[idx].value;

    int idx_l = idx*2+1;
    while (is_not_null(yTree, idx_l)) {
        if (yTree[idx_l].max == -1 || yTree[idx].max <= best_so_far) {
            break;
        }

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
        if (yTree[idx_r].max == -1 || yTree[idx].max <= best_so_far) {
            break;
        }

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

long get_max(const vector<NodeX>& xTree, int xl, int xr, int yl, int yr) {
    long result = 0;

    int idx = 0;
    while (is_not_null(xTree, idx)) {
        if (xTree[idx].key < xl) {
            idx = idx*2+2;
        } else if (xTree[idx].key > xr) {
            idx = idx*2+1;
        } else {
            break;
        }
    }

    if (!is_not_null(xTree, idx)) {
        return result;
    }

    if (yl <= xTree[idx].y && xTree[idx].y <= yr) {
        result = xTree[idx].value;
    }

    int idx_l = idx*2+1;
    while (is_not_null(xTree, idx_l)) {
        if (xTree[idx_l].key >= xl) {
            long tmp = 0;

            if (right_child_is_not_null(xTree, idx_l)) {
                tmp = get_max_y(xTree[idx_l*2+2].yTree, yl, yr, result);
            }

            if (yl <= xTree[idx_l].y && xTree[idx_l].y <= yr && xTree[idx_l].value > tmp) {
                tmp = xTree[idx_l].value;
            }

            if (tmp > result) {
                result = tmp;
            }
        }

        if (xTree[idx_l].key < xl) {
            idx_l = idx_l*2+2;
        } else if (xTree[idx_l].key > xl) {
            idx_l = idx_l*2+1;
        } else {
            break;
        }
    }


    int idx_r = idx*2+2;
    while (is_not_null(xTree, idx_r)) {
        if (xTree[idx_r].key <= xr) {
            long tmp = 0;

            if (left_child_is_not_null(xTree, idx_r)) {
                tmp = get_max_y(xTree[idx_r*2+1].yTree, yl, yr, result);
            }

            if (yl <= xTree[idx_r].y && xTree[idx_r].y <= yr && xTree[idx_r].value > tmp) {
                tmp = xTree[idx_r].value;
            }

            if (tmp > result) {
                result = tmp;
            }
        }

        if (xTree[idx_r].key < xr) {
            idx_r = idx_r*2+2;
        } else if (xTree[idx_r].key > xr) {
            idx_r = idx_r*2+1;
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

void updateX(vector<NodeX>& xTree, int x, int y, long value) {
    int idx = 0;
    while (is_not_null(xTree, idx)) {
        if (idx > 0) {
            updateY(xTree[idx].yTree, y, value);
        }

        if (x < xTree[idx].key) {
            idx = idx*2+1;
        } else if (x > xTree[idx].key) {
            idx = idx*2+2;
        } else {
            xTree[idx].y = y;
            xTree[idx].value = value;
            return;
        }
    }
}

////////////////////////////////////////////////////////////////////////////////

void solve(int n, int d_lat, int d_long, vector<City>& cities) {
    sort(cities.begin(), cities.end(), [](const City& c1, const City& c2) {
        return c1.latitude < c2.latitude;
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

    vector<NodeX> range_tree(points.size()*2);
    make_x_bst(points, range_tree, 0, points.size()-1, 0);

    long result = 0;

    for (auto &c : cities) {
        int x1 = max(0, c.latitude - d_lat);
        int y1 = max(0, c.longitude - d_long);
        int x2 = c.latitude + d_lat;
        int y2 = c.longitude + d_long;

        if (result+c.point < 0) {
            continue;
        }

        long max_points = max(0L, get_max(range_tree, x1, x2, y1, y2));
        max_points += c.point;

        if (max_points > result) {
            result = max_points;
        }

        if (max_points > 0) {
            updateX(range_tree, c.latitude, c.longitude, max_points);
        }
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