#include <bits/stdc++.h>

using namespace std;

struct Task {
    int id;
    int m;
    int d;
    int prio;
};

int solve(vector<Task>& tasks, int x) {
    auto cmp = [](Task &left, Task &right) { return left.prio < right.prio; };

    priority_queue<Task, vector<Task>, decltype(cmp)> queue(cmp);
    for (int i = 0; i < x; i++) {
        queue.push(tasks[i]);
    }

    int ans = 0;
    int time = 1;

    while (!queue.empty()) {
        Task t = queue.top();
        queue.pop();

        if (time - t.d > ans) {
            ans = time - t.d;
        }

        t.m--;
        if (t.m > 0) {
            t.prio--;
            queue.push(t);
        }

        time++;
    }

    return ans;
}

int main(int argc, char** argv) {
    int n;
    cin >> n;

    vector<Task> tasks;
    for (int i = 0; i < n; i++) {
        int d, m;
        cin >> d >> m;
        tasks.push_back({i, m, d, -d+m});
    }

    for (int x = 1; x <= n; x++) {
        cout << solve(tasks, x) << endl;
    }
}

