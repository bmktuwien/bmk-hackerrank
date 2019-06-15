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

bool is_sub_signature(const vector<bool>& s1, const vector<bool>& s2) {
    for (int i = 0; i < s1.size(); i++) {
        if (!s1[i] && s2[i]) {
            return false;
        }
    }

    return true;
}


void solve(int n, int k, vector<vector<pair<int,int>>>& graph, vector<vector<bool>>& signatures) {
    auto cmp = [](Entry &left, Entry &right) { return left.distance > right.distance; };

    priority_queue<Entry, vector<Entry>, decltype(cmp)> queue(cmp);
    vector<set<vector<bool>>> processed(n);
    vector<map<vector<bool>, int>> dist_map(n);

    vector<pair<vector<bool>,int>> candidates;

    queue.push({signatures[0], 0, 0});

    while (!queue.empty()) {
        Entry e = queue.top();
        queue.pop();

        auto it = processed[e.shop].find(e.sig);

        if (it != processed[e.shop].end()) {
            continue;
        }

        processed[e.shop].insert(e.sig);

        if (e.shop == n-1) {
            candidates.push_back(make_pair(e.sig, e.distance));
        }

        for (auto &p : graph[e.shop]) {
            auto sig = add_signatures(e.sig, signatures[p.first]);

            auto it2 = processed[p.first].find(sig);
            if (it2 == processed[p.first].end()) {
                // not processed yet
                int d = INT_MAX;

                auto it3 = dist_map[p.first].find(sig);
                if (it3 != dist_map[p.first].end()) {
                    d = dist_map[p.first][sig];
                }

                if (e.distance + p.second < d) {
                    int d_new = e.distance + p.second;
                    bool useless = false;

                    for (auto &p2 : dist_map[p.first]) {
                        if (is_sub_signature(p2.first, sig) && p2.second < d_new) {
                            useless = true;
                            break;
                        }
                    }

                    if (!useless) {
                        dist_map[p.first][sig] = d_new;
                        queue.push({sig, p.first, d_new});
                    } else {
                        cout << "uesless oida!!!" << endl;
                    }
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

    vector<vector<pair<int,int>>> graph(n, vector<pair<int,int>>());

    for (int i = 0; i < m; i++) {
        int a, b, w;
        cin >> a >> b >> w;
        graph[a-1].push_back(make_pair(b-1,w));
        graph[b-1].push_back(make_pair(a-1,w));
    }

    solve(n, k, graph, signatures);
}
