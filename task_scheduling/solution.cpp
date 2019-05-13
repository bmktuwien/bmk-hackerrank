#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

struct Task {
    int id;
    int m;
    int d;
    int x;
};


int main(int argc, char** argv) {
    int n;
    cin >> n;

    vector<Task> tasks;
    for (int i = 0; i < n; i++) {
        int d, m;
        cin >> d >> m;
        tasks.push_back({i, m, d, -d+m});
    }

    bool all_finished = false;

    int time = 1;
    while (!all_finished) {
        all_finished = true;

        Task *max_task = nullptr;

        for (auto &t : tasks) {
            if (t.m <= 0) {
                continue;
            } else {
                all_finished = false;

                if (max_task == nullptr || t.x > max_task->x) {
                    max_task = &t;
                }
            }
        }

        if (max_task != nullptr) {
            max_task->m--;
            max_task->x--;

            if (max_task->m == 0) {
                cout << "Task " << max_task->id << " finished with overtime: " << time - max_task->d << endl;
            }
        }

        time++;
    }
}

