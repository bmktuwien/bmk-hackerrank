#include <bits/stdc++.h>

using namespace std;

struct City {
    int latitude;
    int longitude;
    int height;
    int point;
};

struct Entry {
    int latitude;
    int longitude;
    int max_points;
};

void solve(int n, int d_lat, int d_long, vector<City>& cities) {
    sort(cities.begin(), cities.end(), [](const City& c1, const City& c2) {
        return c1.height > c2.height;
    });

    int result = 0;
    vector<Entry> acc;
    for (const City& c : cities) {
        int max_points = 0;

        for (const Entry& e : acc) {
            if ((abs(e.latitude-c.latitude) <= d_lat) &&
                    (abs(e.longitude-c.longitude) <= d_long) &&
                    (e.max_points > max_points)) {
                max_points = e.max_points;
            }
        }
        max_points += c.point;

        if (max_points > result) {
            result = max_points;
        }

        acc.push_back({c.latitude, c.longitude, max_points});
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