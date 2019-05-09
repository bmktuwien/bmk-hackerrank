#include <bits/stdc++.h>

using namespace std;

struct Rect {
    long x;
    long y;
    long w;
    long rot;
    long a;
    long b;
    long idx;
};

struct Entry {
    long a;
    long b;
    long d;
};

/////////////////////////////////////////////////////////////////////////////

vector<Rect> build_rect_list(long n, const vector<Entry>& in) {
    vector<Rect> rect_list;

    long x = 0;
    long y = 0;
    long w = n;

    long old_a = 0;
    long old_b = 0;

    rect_list.push_back({x, y, w, 0, 0, 0, 0});

    long rot = 1;

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
                long cnt = (rot-1) % 4;

                if (cnt > 0) {
                    long a1 = e.a;
                    long b1 = e.b;

                    for (long j = 0; j < cnt-1; j++) {
                        long db = b1 - old_b;
                        long da = a1 - old_a;

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
        rect_list.push_back({x, y, w, rot, e.a, e.b, (long)rect_list.size()});
        rot++;
    }

    return rect_list;
}

pair<long,long> query(long k, long n, const vector<Rect>& rect_list) {
    long x = k % n;
    long y = k / n;

    auto it_xl = upper_bound(rect_list.begin(), rect_list.end(), x,
                          [](long x_, const Rect& e) {
                              return x_ < e.x;
                          });
    it_xl--;

    auto it_xr = upper_bound(rect_list.begin(), rect_list.end(), x,
                             [](long x_, const Rect& e) {
                                 return (e.x+e.w) < x_;
                             });
    it_xr--;

    auto it_yl = upper_bound(rect_list.begin(), rect_list.end(), y,
                             [](long y_, const Rect& e) {
                                 return y_ < e.y;
                             });
    it_yl--;

    auto it_yr = upper_bound(rect_list.begin(), rect_list.end(), y,
                             [](long y_, const Rect& e) {
                                 return (e.y+e.w) < y_;
                             });
    it_yr--;


    Rect r = rect_list[min({it_xl->idx, it_xr->idx, it_yl->idx, it_yr->idx})];

    long rot = r.rot % 4;
    long dx = x - r.x;
    long dy = y - r.y;

    long new_x;
    long new_y;

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

int main(int argc, char** argv) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    long n;
    cin >> n;

    long s;
    cin >> s;

    vector<Entry> in;
    for (long i = 0; i < s; i++) {
        long a, b, d;
        cin >> a >> b >> d;
        a--; b--;

        in.push_back({a, b, d});
    }

    auto rect_list = build_rect_list(n, in);

    long l;
    cin >> l;
    while (l--) {
        long k;
        cin >> k;

        auto ans = query(k, n, rect_list);

        cout << ans.second+1 << " " << ans.first+1 << endl;
    }
}