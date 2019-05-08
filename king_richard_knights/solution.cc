#include <bits/stdc++.h>

using namespace std;

struct Rect {
    int x;
    int y;
    int w;
    int idx;
    int a;
    int b;
};

vector<Rect> build_rect_list(int n) {
    vector<Rect> rect_list;

    int s;
    cin >> s;

    int x = 0;
    int y = 0;
    int w = n;
    int idx = 0;

    int old_a = 0;
    int old_b = 0;

    rect_list.push_back({x, y, w, idx, 0, 0});
    idx++;

    while (s--) {
        int a, b, d;
        cin >> a >> b >> d;
        a--; b--;

        if (d == 0) {
            continue;
        }

        if (idx == 1) {
            x = b;
            y = a;
        } else {
            x += a - old_a;
            y += w - b + old_b - d;
        }

        w = d;
        rect_list.push_back({x, y, w, idx, a, b});

        old_a = a;
        old_b = b;
        idx++;
    }

    return rect_list;
}

void query(int k, int n, const vector<Rect>& rect_list) {
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
    cout << "Rect found: " << "k=" << k << " x=" << r.x << " y=" << r.y << " w=" << r.w << " rot=" << r.idx << endl;

    int rot = r.idx % 4;
    int dx = x - r.x;
    int dy = y - r.y;

    int new_x;
    int new_y;

    if (rot == 0) {
        new_x = x;
        new_y = y;
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

    cout << new_y+1 << " " << new_x+1 << endl;
}

int main(int argc, char** argv) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    auto rect_list = build_rect_list(n);

    int l;
    cin >> l;
    while (l--) {
        int k;
        cin >> k;

        query(k, n, rect_list);
    }
}