#include <bits/stdc++.h>

using namespace std;

struct City {
    int latitude;
    int longitude;
    int height;
    int point;
};


////////////////////////////////////////////////////////////////////////////////

class CompressedSegmentationTree {
public:
    void build(const vector<int>& v) {
        _n = v.size();
        _t.resize(_n*4, 0);

        for (int i = 0; i < v.size(); i++) {
            _m[v[i]] = i;
        }
    }

    void update(int pos, long val) {
        pos = _m[pos];

        _update(1, 0, _n-1, pos, val);
    }

    long get_max(int pos_l, int pos_r) {
        auto it_l = _m.lower_bound(pos_l);
        auto it_r = _m.upper_bound(pos_r);

        if (it_r == it_l) {
            return 0;
        }

        if (it_r != _m.begin()) {
            it_r--;
        }

        return _get_max(1, 0, _n-1, (*it_l).second, (*it_r).second);
    }

private:
    void _update(int v, int tl, int tr, int pos, long new_val) {
        if (tl == tr) {
            _t[v] = max(_t[v], new_val);
        } else {
            int tm = (tl + tr) / 2;
            if (pos <= tm)
                _update(v*2, tl, tm, pos, new_val);
            else
                _update(v*2+1, tm+1, tr, pos, new_val);

            _t[v] = max(_t[v*2], _t[v*2+1]);
        }
    }

    long _get_max(int v, int tl, int tr, int l, int r) {
        if (l > r) {
            return 0;

        }
        if (l == tl && r == tr) {
            return _t[v];
        }
        int tm = (tl + tr) / 2;
        return max(_get_max(v*2, tl, tm, l, min(r, tm)),
                   _get_max(v*2+1, tm+1, tr, max(l, tm+1), r));
    }

    size_t _n = 0;
    map<int, int> _m;
    vector<long> _t;
};

////////////////////////////////////////////////////////////////////////////////

class SegmentationTree2D {
public:
    explicit SegmentationTree2D(const vector<pair<int,int>>& points, int max_n)
            : _max_n(max_n){
        _t.resize((max_n+1)*4);
        _build(points, 1, 1, max_n);
    }

    void update(int x, int y, long new_val) {
        _update(1, 1, _max_n, x, y, new_val);
    }

    long get_max(int x1, int y1, int x2, int y2) {
        //cout << "crap: " << x1 << " - " << x2 << endl;
        return _get_max(1, 1, _max_n, x1, y1, x2, y2);
    }

private:
    long _get_max(int v, int tl, int tr, int x1, int y1, int x2, int y2) {
        //cout << "fuck: " << tl << " - " << tr << endl;
        if (x1 > x2) {
            //cout << "break!!!" << endl;
            return 0;
        }

        if (x1 == tl && x2 == tr) {
            //cout << "bingo!!!" << endl;
            //return _t[v].get_max(y1, y2);
            return tl-x1;
        }
        int tm = (tl + tr) / 2;
        return max(_get_max(v*2, tl, tm, x1, y1, min(x2, tm), y2),
                   _get_max(v*2+1, tm+1, tr, max(x1, tm+1), y1, x2, y2));
    }

    void _update(int v, int tl, int tr, int x, int y, long new_val) {
        if (tl == tr) {
            _t[v].update(y, new_val);
        } else {
            int tm = (tl + tr) / 2;
            _t[v].update(y, new_val);

            if (x <= tm) {
                _update(v*2, tl, tm, x, y, new_val);
            } else {
                _update(v*2+1, tm+1, tr, x, y, new_val);
            }
        }
    }

    void _build(const vector<pair<int,int>>& points, int v, int tl, int tr) {
        vector<int> ys;
        for (auto &p : points) {
            ys.push_back(p.second);
        }
        sort(ys.begin(), ys.end());

        if (tl == tr) {
            _t[v].build(ys);
        } else {
            int tm = (tl + tr) / 2;
            vector<pair<int,int>> points_l, points_r;
            for (auto &p : points) {
                if (p.first <= tm) {
                    points_l.push_back(p);
                } else {
                    points_r.push_back(p);
                }
            }

            _t[v].build(ys);
            _build(points_l, v*2, tl, tm);
            _build(points_r, v*2+1, tm+1, tr);
        }
    }

    int _max_n;
    vector<CompressedSegmentationTree> _t;
};

////////////////////////////////////////////////////////////////////////////////

void solve(int n, int d_lat, int d_long, vector<City>& cities) {
    sort(cities.begin(), cities.end(), [](const City& c1, const City& c2) {
        return c1.height > c2.height;
    });

    vector<pair<int,int>> points;
    for (auto &c : cities) {
        points.emplace_back(c.latitude, c.longitude);
    }
    sort(points.begin(), points.end());

    SegmentationTree2D seg_tree(points, 200000);

    long result = 0;
    for (const City& c : cities) {
        int x1 = max(1, c.latitude - d_lat);
        int y1 = max(1, c.longitude - d_long);
        int x2 = min(c.latitude + d_lat, 200000);
        int y2 = min(c.longitude + d_long, 200000);

        long max_points = seg_tree.get_max(x1, y1, x2, y2);
        max_points += c.point;

        seg_tree.update(c.latitude, c.longitude, max_points);

        if (max_points > result) {
            result = max_points;
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