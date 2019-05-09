#include <bits/stdc++.h>

using namespace std;

struct Rect {
    int x;
    int y;
    int w;
    int rot;
    int a;
    int b;
    int idx;
};

struct Entry {
    int a;
    int b;
    int d;
};

/////////////////////////////////////////////////////////////////////////////

void rotate_90(vector<vector<int>> &a, int p, int q, int d) {

    for (int i = 0; i < d / 2; i++) {
        for (int j = i; j < d - i - 1; j++) {

            // Swap elements of each cycle
            // in clockwise direction
            int temp = a[p+i][q+j];
            a[p+i][q+j] = a[p + d - 1 - j][q + i];
            a[p + d - 1 - j][q + i] = a[p + d - 1 - i][q + d - 1 - j];
            a[p + d - 1 - i][q + d - 1 - j] = a[p + j][q + d - 1 - i];
            a[p + j][q + d - 1 - i] = temp;
        }
    }
}

void print_matrix(vector<vector<int>> &a) {
    for (int i = 0; i < a.size(); i++) {
        for (int j = 0; j < a.size(); j++)
            cout << std::setw(5) << a[i][j] << " ";
        cout << endl;
    }
}

vector<Rect> build_rect_list(int n, const vector<Entry>& in) {
    vector<Rect> rect_list;

    int x = 0;
    int y = 0;
    int w = n;

    int old_a = 0;
    int old_b = 0;

    rect_list.push_back({x, y, w, 0, 0, 0, 0});

    int rot = 1;

    for (auto &e : in) {
        if (e.d == 0) {
            continue;
        }

        if (rot == 1) {
            x = e.b;
            y = e.a;
        } else {
            if (old_a == e.a && old_b == e.b && w == e.d) {
                rect_list.back().rot = rot;

                rot++;
                continue;
            } else {
                int cnt = (rot-1) % 4;

                if (cnt > 0) {
                    int a1 = e.a;
                    int b1 = e.b;

                    for (int j = 0; j < cnt-1; j++) {
                        int db = b1 - old_b;
                        int da = a1 - old_a;

                        b1 = old_b + da;
                        a1 = old_a + w - db - e.d;
                    }

                    x += a1 - old_a;
                    y += w - b1 + old_b - e.d;
                } else {
                    x += e.b - old_b;
                    y += e.a - old_a;
                }
            }
        }

        w = e.d;

        old_a = e.a;
        old_b = e.b;
        rect_list.push_back({x, y, w, rot, e.a, e.b, (int)rect_list.size()});
        rot++;
    }

    return rect_list;
}

pair<int,int> query(int k, int n, const vector<Rect>& rect_list) {
    int x = k % n;
    int y = k / n;

    auto it_xl = upper_bound(rect_list.begin(), rect_list.end(), x,
                          [](int x_, const Rect& e) {
                              return x_ < e.x;
                          });
    it_xl--;

    auto it_xr = upper_bound(rect_list.begin(), rect_list.end(), x,
                             [](int x_, const Rect& e) {
                                 return (e.x+e.w) < x_;
                             });
    it_xr--;

    auto it_yl = upper_bound(rect_list.begin(), rect_list.end(), y,
                             [](int y_, const Rect& e) {
                                 return y_ < e.y;
                             });
    it_yl--;

    auto it_yr = upper_bound(rect_list.begin(), rect_list.end(), y,
                             [](int y_, const Rect& e) {
                                 return (e.y+e.w) < y_;
                             });
    it_yr--;


    Rect r = rect_list[min({it_xl->idx, it_xr->idx, it_yl->idx, it_yr->idx})];
    //cout << "Rect found: " << "k=" << k << " x=" << r.x << " y=" << r.y << " w=" << r.w << " rot=" << r.rot << endl;

    int rot = r.rot % 4;
    int dx = x - r.x;
    int dy = y - r.y;

    int new_x;
    int new_y;

    if (rot == 0) {
        new_x = r.b + dx;
        new_y = r.a + dy;
    } else if (rot == 1) {
        new_x = r.b + (r.w-dy);
        new_y = r.a + dx;
    } else if (rot == 2) {
        new_x = r.b + (r.w-dx);
        new_y = r.a + (r.w-dy);
    } else {
        new_x = r.b + dy;
        new_y = r.a + (r.w-dx);
    }

    return {new_x, new_y};
}

/////////////////////////////////////////////////////////////////////////////

void debug(int n) {
    vector<Entry> in;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < i; j++) {
            in.push_back({i,i,n-1-i});
        }
    }

    vector<vector<int>> naive_matrix;
    for (int i = 0; i < n; i++) {
        vector<int> v;
        for (int j = 0; j < n; j++) {
            v.push_back(i*n+j);
        }
        naive_matrix.push_back(v);
    }

    auto rect_list = build_rect_list(n, in);

    for (auto &e : in) {
        rotate_90(naive_matrix, e.a, e.b, e.d+1);
    }

    print_matrix(naive_matrix);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            auto ans = query(naive_matrix[i][j], n, rect_list);

            if (ans.first != j || ans.second != i) {
                cout << "error: " << "elem=" << naive_matrix[i][j] << " x=" << j << " y=" << i << " ans.x=" << ans.first << " ans.y=" << ans.second << endl;
            }
        }
    }

}

int main(int argc, char** argv) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    //debug(n);
    //return 0;

    int s;
    cin >> s;

    vector<Entry> in;
    for (int i = 0; i < s; i++) {
        int a, b, d;
        cin >> a >> b >> d;
        a--; b--;

        in.push_back({a, b, d});
    }

    auto rect_list = build_rect_list(n, in);

    int l;
    cin >> l;
    while (l--) {
        int k;
        cin >> k;

        auto ans = query(k, n, rect_list);

        cout << ans.second+1 << " " << ans.first+1 << endl;
    }
}