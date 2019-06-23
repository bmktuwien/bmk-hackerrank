#include <bits/stdc++.h>

using namespace std;

struct Node {
    long key;
    long max;
    long max_right;
    long lazy_propagation;
    long propagated;
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
    root->max = numeric_limits<int>::min();
    root->max_right = numeric_limits<int>::min();
    root->lazy_propagation = 0;
    root->propagated = 0;


    root->left = buildBST(start, mid - 1);
    root->right = buildBST(mid + 1, end);

    return root;
}

long updateBST(Node *node, Task& task, int rank, int lazy_propagation) {
    if (node == nullptr) {
        return numeric_limits<int>::min();
    }

    if (rank > node->key) {
        long m1 = updateBST(node->right, task, rank, lazy_propagation + node->lazy_propagation);
        long m2 = node->max_right + lazy_propagation + node->lazy_propagation - node->propagated;

        long max_right = max(m1, m2);

        if (max_right > node->max_right) {
            node->max_right = max_right;
            node->propagated = lazy_propagation + node->lazy_propagation;
        }

        node->max = max(node->max, node->max_right);
    } else {
        long m1 = numeric_limits<int>::min();
        if (rank == node->key) {
            m1 = lazy_propagation + node->lazy_propagation + task.m - task.d;
        }

        long m2 = node->max_right + lazy_propagation + node->lazy_propagation + task.m
                  - node->propagated;

        long m3 = updateBST(node->left, task, rank, lazy_propagation);


        long max_right = max(m1, m2);
        if (max_right > node->max_right) {
            node->max_right = max_right;
            node->propagated = lazy_propagation + node->lazy_propagation + task.m;
        }

        node->lazy_propagation += task.m;

        node->max = max(max(m1, m2), m3);
    }


    return node->max;
}


vector<int> solve2(vector<Task>& tasks) {
    vector<int> res;

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
        res.push_back(max(0, ans));
    }

    return res;
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

    auto res = solve2(tasks);
    for (auto i : res) {
        cout << i << endl;
    }

}

