#include <bits/stdc++.h>

using namespace std;

struct Entry {
    int node;
    int penalty;
};

void solve(int n, vector<vector<pair<int,int>>>& graph, int a, int b) {
    queue<Entry> q;
    vector<vector<bool>> marked(n, vector<bool>(1024, false));

    q.push({a, 0});

    int ans = -1;

    while (!q.empty()) {
        Entry e = q.front();
        q.pop();

        if (e.node == b) {
            if (ans == -1) {
                ans = e.penalty;
            } else {
                if (e.penalty < ans) {
                    ans = e.penalty;
                }
            }
        }

        for (auto &p : graph[e.node]) {
            int node = p.first;
            int w = p.second;

            int p_new = e.penalty | w;

            if (!marked[node][p_new]) {
                marked[node][p_new] = true;
                q.push({node, p_new});
            }
        }
    }

    cout << ans << endl;
}

int main(int argc, char **argv) {
    int n, m;
    cin >> n >> m;

    vector<vector<pair<int,int>>> graph(n, vector<pair<int,int>>());

    for (int i = 0; i < m; i++) {
        int a, b, w;
        cin >> a >> b >> w;
        graph[a-1].push_back(make_pair(b-1,w));
        graph[b-1].push_back(make_pair(a-1,w));
    }

    int a, b;
    cin >> a >> b;

    solve(n, graph, a-1, b-1);
}
