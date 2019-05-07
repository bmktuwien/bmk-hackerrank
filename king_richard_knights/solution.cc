#include <bits/stdc++.h>

using namespace std;

struct Entry {
    int x;
    int y;
    int w;
    int rot;
};

map<int, Entry> lkup_map;

void build_map(int n) {
    int s;
    cin >> s;

    int x = 0;
    int y = 0;
    int w = n;
    int rot = 0;

    int old_a = 0;
    int old_b = 0;

    lkup_map[0] = {0, 0, n, 0};

    while (s--) {
        int a, b, d;
        cin >> a >> b >> d;
        a--; b--;

        if (d == 0) {
            continue;
        }

        if (rot == 0) {
            x = b;
            y = a;
        } else {
            x += a - old_a;
            y += w - b + old_b - d;
        }

        w = d;
        lkup_map[x] = {x, y, w, rot};

        old_a = a;
        old_b = b;
        rot++;
    }
}

int main(int argc, char** argv) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    build_map(n);
    cout << "done" << endl;
}