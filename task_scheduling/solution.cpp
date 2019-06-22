#include <bits/stdc++.h>

using namespace std;

struct Node {
    int key;
    int max_overtime;
    int lazy_propagation;
    Node* left;
    Node* right;
};

struct Task {
    int id;
    int m;
    int d;
};

Node* buildBST(int start, int end) {
    if (start > end) {
        return nullptr;
    }

    int mid = (start + end)/2;
    auto *root = new Node();
    root->key = mid;
    root->max_overtime = 0;
    root->lazy_propagation = 0;


    root->left = buildBST(start, mid - 1);
    root->right = buildBST(mid + 1, end);

    return root;
}

int updateBST(Node *node, Task& task, int rank, int lazy_propagation) {
    if (node == nullptr) {
        return 0;
    }

    int new_max;

    if (rank == node->key) {
        lazy_propagation += node->lazy_propagation;

        new_max = (lazy_propagation + task.m) - task.d;
        node->lazy_propagation += task.m;
    } else if (rank > node->key) {
        new_max = updateBST(node->right, task, rank, lazy_propagation + node->lazy_propagation);
    } else {
        node->lazy_propagation += task.m;

        int m1 = node->max_overtime + lazy_propagation;
        int m2 = updateBST(node->left, task, rank, lazy_propagation);

        new_max = max(m1, m2);
    }

    if (node->max_overtime < new_max) {
        node->max_overtime = new_max;
    }

    return node->max_overtime;
}

void solve(vector<Task>& tasks) {
    for (int i = 0; i < tasks.size(); i++) {
        vector<Task> tasks_copy(tasks.begin(), tasks.begin()+i+1);

        std::sort(tasks_copy.begin(), tasks_copy.end(), [](Task &left, Task &right) {
            return left.d < right.d;
        });

        int ans = 0;
        int acc = 0;

        for (int j = 0; j <= i; j++) {
            acc += tasks_copy[j].m;
            if (tasks_copy[j].d  < acc) {
                if (ans < acc - tasks_copy[j].d) {
                    ans = acc - tasks_copy[j].d;
                }
            }
        }

        cout << ans << endl;
    }
}

void solve2(vector<Task>& tasks) {
    vector<Task> tasks_sorted(tasks.begin(), tasks.end());

    std::sort(tasks_sorted.begin(), tasks_sorted.end(), [](Task &left, Task &right) {
        return left.d < right.d;
    });

    vector<int> task_ranks(tasks_sorted.size());
    for (int i = 0; i < tasks_sorted.size(); i++) {
        task_ranks[tasks_sorted[i].id] = i;
    }

    auto *bst = buildBST(0, tasks_sorted.size()-1);

    for (auto &task : tasks) {
        int ans = updateBST(bst, task, task_ranks[task.id], 0);
        cout << ans << endl;
    }
}

int main(int argc, char** argv) {
    int n;
    cin >> n;

    vector<Task> tasks;
    for (int i = 0; i < n; i++) {
        int d, m;
        cin >> d >> m;
        tasks.push_back({i, m, d});
    }

    /*for (int x = 1; x <= n; x++) {
        cout << solve(tasks, x) << endl;
    }*/
    solve2(tasks);
}

