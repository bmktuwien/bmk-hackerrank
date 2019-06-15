#include <bits/stdc++.h>

using namespace std;

struct Entry {
    vector<bool> sig;
    int shop;
    int distance;
};

vector<bool> add_signatures(vector<bool>& s1, vector<bool>& s2) {
    vector<bool> sig(s1.size(), false);

    for (int i = 0; i < s1.size(); i++) {
        sig[i] = s1[i] || s2[i];
    }

    return sig;
}


void solve(int n, int k, vector<vector<int>>& graph, vector<vector<bool>>& signatures) {
    auto cmp = [](Entry &left, Entry &right) { return left.distance > right.distance; };

    priority_queue<Entry, vector<Entry>, decltype(cmp)> queue(cmp);
    set<pair<int,vector<bool>>> processed;
    map<pair<int,vector<bool>>, int> dist_map;

    vector<pair<vector<bool>,int>> candidates;

    queue.push({signatures[0], 0, 0});

    while (!queue.empty()) {
        Entry e = queue.top();
        queue.pop();

        auto key = make_pair(e.shop, e.sig);
        auto it = processed.find(key);

        if (it != processed.end()) {
            continue;
        }

        processed.insert(key);

        if (e.shop == n-1) {
            candidates.push_back(make_pair(e.sig, e.distance));
        }

        for (int shop = 0; shop < n; shop++) {
            if (graph[e.shop][shop] == 0) {
                continue;
            }

            auto sig = add_signatures(e.sig, signatures[shop]);
            auto key2 = make_pair(shop, sig);

            auto it2 = processed.find(key2);
            if (it2 == processed.end()) {
                // not processed yet
                int d = INT_MAX;

                auto it3 = dist_map.find(key2);
                if (it3 != dist_map.end()) {
                    d = dist_map[key2];
                }

                if (e.distance+graph[e.shop][shop] < d) {
                    dist_map[key2] = e.distance+graph[e.shop][shop];
                    queue.push({sig, shop, e.distance+graph[e.shop][shop]});
                }
            }
        }
    }

    int ans = INT_MAX;

    for (int i = 0; i < candidates.size(); i++) {
        for (int j = i; j < candidates.size(); j++) {
            auto sig = add_signatures(candidates[i].first, candidates[j].first);

            bool all_fish = true;

            for (auto b : sig) {
                if (!b) {
                    all_fish = false;
                    break;
                }
            }

            if (all_fish) {
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

    vector<vector<bool>> signatures;

    for (int i = 0; i < n; i++) {
        int f;
        cin >> f;

        vector<bool> sig(k, false);
        for (int j = 0; j < f; j++) {
            int ft;
            cin >> ft;
            sig[ft-1] = true;
        }

        signatures.push_back(sig);
    }

    vector<vector<int>> graph(n, vector<int>(n, 0));

    for (int i = 0; i < m; i++) {
        int a, b, w;
        cin >> a >> b >> w;
        graph[a-1][b-1] = w;
        graph[b-1][a-1] = w;
    }

    solve(n, k, graph, signatures);
}
