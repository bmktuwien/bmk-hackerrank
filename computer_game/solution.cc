#include <bits/stdc++.h>

using namespace std;

struct Entry {
    int node;
    int eid;
    int eid_r;
};

vector<int> gen_primes(int n) {
    vector<int> result;

    bool prime[n+1];
    memset(prime, true, sizeof(prime));

    for (int p=2; p*p<=n; p++) {
        if (prime[p]) {
            for (int i=p*2; i<=n; i += p)
                prime[i] = false;
        }
    }

    // Print all prime numbers
    for (int p=2; p<=n; p++) {
        if (prime[p]) {
            result.push_back(p);
        }
    }

    return result;
}

vector<int> factorization(int n, const vector<int>& primes) {
    vector<int> a;

    if (!(n&1)) {
        a.push_back(2);
        n >>= 1;

        while (!(n&1)) {
            n >>= 1;
        }
    }

    int i = 1;
    int f = primes[i];

    while (f*f <= n) {
        if (n % f == 0) {
            a.push_back(f);
            n /= f;

            while (n % f == 0) {
                n /= f;
            }
        }
        f = primes[i++];
    }

    if (n != 1) {
        a.push_back(n);
    }

    return a;
}

bool bfs(const vector<vector<Entry>> &graph,
         vector<int>& cap_edges, vector<int>& level, int s, int t) {
    queue<int> q;
    q.push(s);
    level[s] = 1;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (const Entry &e : graph[u]) {
            if ((level[e.node] == 0) && (cap_edges[e.eid] > 0)) {
                level[e.node] = level[u] + 1;
                q.push(e.node);
            }
        }
    }

    return level[t] > 0;
}

int dfs(const vector<vector<Entry>> &graph,
        vector<int>& ptr, vector<int>& cap_edges, vector<int>& level,
        int u, int s, int t) {

    if (u == t) {
        return 1;
    }

    for (int i = ptr[u]; i < graph[u].size(); i++) {
        const Entry& e = graph[u][i];
        ptr[u] = i;

        if ((level[e.node] == level[u]+1) && (cap_edges[e.eid] > 0)) {
            int f = dfs(graph, ptr, cap_edges, level, e.node, s, t);
            if (f > 0) {
                cap_edges[e.eid] -= f;
                cap_edges[e.eid_r] += f;
                return f;
            }
        }
    }

    return 0;
}

int max_flow(const vector<vector<Entry>> &graph, vector<int>& cap_edges,
             int s, int t) {
    int n = graph.size();
    vector<int> level(n, 0);
    vector<int> ptr(n, 0);

    int flow = 0;

    while (bfs(graph, cap_edges, level, s, t)) {
        int f;
        do {
            f = dfs(graph, ptr, cap_edges, level, s, s, t);
            flow += f;
        } while(f > 0);

        fill(level.begin(), level.end(), 0);
        fill(ptr.begin(), ptr.end(), 0);
    }

    return flow;
}

void solve(int n, const vector<int>& A, const vector<int>& B) {
    vector<int> primes = gen_primes(32000);

    int start_node = 0;
    int end_node = 1;

    vector<vector<Entry>> graph(310000);
    vector<int> cap_edges;
    int node_count = 2;
    int edge_count = 0;
    map<int, int> prime_nodes_map;

    for (int value : A) {
        int current_node = node_count;

        graph[start_node].push_back({current_node, edge_count, edge_count+1});
        cap_edges.push_back(1);
        graph[current_node].push_back({start_node, edge_count+1, edge_count});
        cap_edges.push_back(0);
        edge_count += 2;
        node_count += 1;

        vector<int> prime_factors = factorization(value, primes);
        for (int p : prime_factors) {
            auto it = prime_nodes_map.find(p);
            if (it == prime_nodes_map.end()) {
                prime_nodes_map[p] = node_count;
                node_count += 1;
            }

            int p_node = prime_nodes_map[p];
            graph[current_node].push_back({p_node, edge_count, edge_count+1});
            cap_edges.push_back(1);

            graph[p_node].push_back({current_node, edge_count+1, edge_count});
            cap_edges.push_back(0);
            edge_count += 2;
        }
    }

    for (int value : B) {
        int current_node = node_count;
        graph[current_node].push_back({end_node, edge_count, edge_count+1});
        cap_edges.push_back(1);

        graph[end_node].push_back({current_node, edge_count+1, edge_count});
        cap_edges.push_back(0);
        edge_count += 2;
        node_count += 1;

        vector<int> prime_factors = factorization(value, primes);
        for (int p : prime_factors) {
            auto it = prime_nodes_map.find(p);
            if (it == prime_nodes_map.end()) {
                prime_nodes_map[p] = node_count;
                node_count += 1;
            }

            int p_node = prime_nodes_map[p];
            graph[p_node].push_back({current_node, edge_count, edge_count+1});
            cap_edges.push_back(1);

            graph[current_node].push_back({p_node, edge_count+1, edge_count});
            cap_edges.push_back(0);
            edge_count += 2;
        }
    }

    cout << max_flow(graph, cap_edges, start_node, end_node) << endl;
}

int main(int argc, char **argv) {
    int n;
    cin >> n;

    vector<int> a;
    for (int i = 0; i < n; i++) {
        int val;
        cin >> val;
        a.push_back(val);
    }

    vector<int> b;
    for (int i = 0; i < n; i++) {
        int val;
        cin >> val;
        b.push_back(val);
    }

    solve(n, a, b);
}