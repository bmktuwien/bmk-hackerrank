#include <bits/stdc++.h>

using namespace std;

struct Entry {
    int node;
    int penalty;
};

void solve(int n, vector<vector<pair<int,int>>>& graph, int a, int b) {
    auto cmp = [](Entry &left, Entry &right) { return left.penalty > right.penalty; };

    priority_queue<Entry, vector<Entry>, decltype(cmp)> queue(cmp);
    vector<bool> processed(n, false);
    vector<int> penalty(n, -1);

    queue.push({a, 0});

    while (!queue.empty()) {
        Entry e = queue.top();
        queue.pop();

        if (e.node == b) {
            break;
        }

        processed[e.node] = true;

        for (auto &p : graph[e.node]) {
            int node = p.first;
            int w = p.second;

            if (!processed[node]) {
                int pen = INT_MAX;

                if (penalty[node] != -1) {
                    pen = penalty[node];
                }

                if (e.penalty | w < pen) {
                    int p_new = e.penalty | w;

                    penalty[node] = p_new;
                    queue.push({node, p_new});
                }
            }
        }
    }

    cout << penalty[b] << endl;
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
