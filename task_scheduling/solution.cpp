#include <vector>
#include <iostream>

using namespace std;

struct Task {
    int d;
    int m;
};


int main(int argc, char** argv) {
    int n;
    cin >> n;

    vector<Task> tasks;
    for (int i = 0; i < n; i++) {
        int d, m;
        cin >> d >> m;
        tasks.push_back({d, m});
    }

}

