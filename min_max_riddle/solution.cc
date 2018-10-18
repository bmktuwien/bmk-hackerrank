#include <vector>
#include <iostream>
#include <map>

int main() {
    int n;

    std::cin >> n;

    std::vector<long> v;
    std::map<long, int, std::greater<long>> m;

    for (int i = 0; i < n; i++) {
        long l;
        std::cin >> l;

        m[l] = i;
        v.push_back(l);
    }

    std::vector<bool> visited(n);
    long x = 0;

    for (const auto& p : m) {
        if (visited[p.second]) {
            continue;
        }

        int q = 1;
        visited[p.second] = true;
        // search right
        for (int i = p.second+1; i < n; i++) {
            if (v[i] < p.first) {
                break;
            }

            visited[i] = true;
            q++;
        }

        // search left
        for (int i = p.second-1; i >= 0; i--) {
            if (v[i] < p.first) {
                break;
            }

            visited[i] = true;
            q++;
        }

        while (x < q) {
            std::cout << p.first << " ";
            x++;
        }
    }
    std::cout << std::endl;
}
