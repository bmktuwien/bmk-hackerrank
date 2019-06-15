#include <bits/stdc++.h>

using namespace std;

struct Entry {
    vector<bool> sig;
    vector<int> dist;
    vector<bool> visited;
};

int min_distance(int n, vector<int>& dist, vector<bool>& visited)
{
    int min = INT_MAX, min_index = -1;

    for (int i = 0; i < n; i++) {
        if (!visited[i] && dist[i] <= min) {
            min = dist[i];
            min_index = i;
        }
    }

    return min_index;
}

vector<bool> fish_signature(int k, int i, vector<vector<int>>& fish_list) {
    vector<bool> sig(k, false);

    for (auto f : fish_list[i]) {
        sig[f] = true;
    }

    return sig;
}

bool is_sub_signature(const vector<bool>& s1, const vector<bool>& s2) {
    for (int i = 0; i < s1.size(); i++) {
        if (s1[i] == 0 && s2[i] == 1) {
            return false;
        }
    }

    return true;
}

void update_dist_matrix(vector<Entry>& dist_matrix, vector<bool>& sig, int n, int k,
                        int u, int v, int d) {

    for (auto &e : dist_matrix) {
        if (is_sub_signature(e.sig, sig)) {

        }
    }

    Entry e{sig, };
    auto &dist = dist_map[sig].first;
    auto &visited = dist_map[sig].second;

    if (!visited[v] && dist[u]+d < dist[v]) {
        dist[v] = dist[u]+d;
    }
}

void solve(int n, vector<vector<int>>& graph, vector<vector<int>>& fish_list) {
    map<vector<bool>, pair<vector<int>, vector<bool>>> dist;

    dist[0] = 0;
    int u = 0;

    while (u != -1) {
        visited[u] = true;
        for (int i = 0; i < n; i++) {
            if (graph[u][i] == 0 || visited[i]) {
                continue;
            }

            if (dist[i] != INT_MAX && dist[u])
        }
    }
}

int main(int argc, char **argv) {
    int n, m, k;
    cin >> n >> m >> k;

    vector<vector<int>> fish_list;

    for (int i = 0; i < n; i++) {
        int f;
        cin >> f;

        vector<int> v;
        for (int j = 0; j < f; j++) {
            int ft;
            cin >> ft;
            v.push_back(ft);
        }

        fish_list.push_back(v);
    }

    vector<vector<int>> graph(n, vector<int>(n, 0));

    for (int i = 0; i < m; i++) {
        int a, b, w;
        cin >> a >> b >> w;
        graph[a-1][b-1] = w;
        graph[b-1][a-1] = w;
    }
}
