#include <bits/stdc++.h>

using namespace std;

struct Entry {
    int sig;
    int shop;
    int distance;
};

void solve(int n, int k, vector<vector<pair<int,int>>>& graph, vector<int>& signatures) {
    auto cmp = [](Entry &left, Entry &right) { return left.distance > right.distance; };

    priority_queue<Entry, vector<Entry>, decltype(cmp)> queue(cmp);
    vector<vector<bool>> processed(n, vector<bool>(1024, false));
    vector<vector<int>> dist_map(n, vector<int>(1024, -1));

    vector<pair<int,int>> candidates;

    queue.push({signatures[0], 0, 0});

    while (!queue.empty()) {
        Entry e = queue.top();
        queue.pop();

        if (processed[e.shop][e.sig]) {
            continue;
        }

        processed[e.shop][e.sig] = true;

        if (e.shop == n-1) {
            candidates.push_back(make_pair(e.sig, e.distance));
        }

        for (auto &p : graph[e.shop]) {
            auto sig = e.sig | signatures[p.first];

            if (!processed[p.first][sig]) {
                // not processed yet
                int d = INT_MAX;

                if (dist_map[p.first][sig] != -1) {
                    d = dist_map[p.first][sig];
                }

                if (e.distance + p.second < d) {
                    int d_new = e.distance + p.second;

                    dist_map[p.first][sig] = d_new;
                    queue.push({sig, p.first, d_new});
                }
            }
        }
    }


    int ans = INT_MAX;

    for (int i = 0; i < candidates.size(); i++) {
        for (int j = i; j < candidates.size(); j++) {
            auto sig = candidates[i].first | candidates[j].first;

            if (sig == (1 << k) - 1) {
                int t = max(candidates[i].second, candidates[j].second);
                if (t < ans) {
                    ans = t;
                }
            }
        }
    }

    cout << ans << endl;
}

int main(int argc, char **argv) {
    int n, m, k;
    cin >> n >> m >> k;

    vector<int> signatures;

    for (int i = 0; i < n; i++) {
        int f;
        cin >> f;

        int sig = 0;
        for (int j = 0; j < f; j++) {
            int ft;
            cin >> ft;
            sig |= (1 << (ft-1));
        }

        signatures.push_back(sig);
    }

    vector<vector<pair<int,int>>> graph(n, vector<pair<int,int>>());

    for (int i = 0; i < m; i++) {
        int a, b, w;
        cin >> a >> b >> w;
        graph[a-1].push_back(make_pair(b-1,w));
        graph[b-1].push_back(make_pair(a-1,w));
    }

    solve(n, k, graph, signatures);
}
