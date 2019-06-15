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

    queue.push({signatures[0], 0, 0});

    while (!queue.empty()) {
        Entry e = queue.top();
        queue.pop();

        processed.insert(make_pair(e.shop, e.sig));

        for (int shop = 0; shop < n; shop++) {
            if (graph[e.shop][shop] == 0) {
                continue;
            }

            auto sig = add_signatures(e.sig, signatures[shop]);
            auto key = make_pair(shop, sig);

            auto it = processed.find(key);
            if (it == processed.end()) {
                // not processed yet
                int d = INT_MAX;

                auto it2 = dist_map.find(key);
                if (it2 != dist_map.end()) {
                    d = dist_map[key];
                }

                if (e.distance+graph[e.shop][shop] < d) {
                    dist_map[key] = e.distance+graph[e.shop][shop];
                    queue.push({sig, shop, e.distance+graph[e.shop][shop]});
                }
            }
        }
    }

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
