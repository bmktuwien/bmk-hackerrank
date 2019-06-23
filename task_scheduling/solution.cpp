#include <bits/stdc++.h>

using namespace std;

struct Node {
    int key;
    int max_overtime;
    int lazy_propagation;
    int propagated;
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
    root->max_overtime = numeric_limits<int>::min();
    root->lazy_propagation = 0;
    root->propagated = 0;


    root->left = buildBST(start, mid - 1);
    root->right = buildBST(mid + 1, end);

    return root;
}

int updateBST(Node *node, Task& task, int rank, int lazy_propagation) {
    if (node == nullptr) {
        return 0;
    }

    int new_max;

    if (rank > node->key) {
        node->propagated = lazy_propagation + node->lazy_propagation;
        new_max = updateBST(node->right, task, rank, lazy_propagation + node->lazy_propagation);
    } else {
        int m1;
        if (rank == node->key) {
            m1 = lazy_propagation + node->lazy_propagation + task.m - task.d;
        } else {
            m1 = updateBST(node->left, task, rank, lazy_propagation);
        }

        lazy_propagation += node->lazy_propagation;
        node->lazy_propagation += task.m;

        int m2 = node->max_overtime + lazy_propagation - node->propagated + task.m;

        int m3 = numeric_limits<int>::min();
        if (node->right != nullptr) {
            m3 = node->right->max_overtime + lazy_propagation + task.m
                 - node->right->propagated;
        }

        node->propagated = lazy_propagation + task.m;
        new_max = max(max(m1, m2), m3);
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

        cout << max(0, ans) << endl;
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
        cout << max(0,ans) << endl;
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
    solve(tasks);
    cout << "============" << endl;
    solve2(tasks);
}

