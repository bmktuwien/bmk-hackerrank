#include <algorithm>
#include <vector>
#include <iostream>
#include <map>
#include <set>


void brute_force_debug(int a, int b, int c, int d) {
    std::vector<int> v({a,b,c,d});
    std::sort(v.begin(), v.end());

    std::map<int,int> m;
    int res = 0;

    int t = 0;
    for (int a = 1; a <= v[0]; a++) {
        for (int b = a; b <= v[1]; b++) {
            for (int c = b; c <= v[2]; c++) {
                for (int d = c; d <= v[3]; d++) {
                    m[a^b^c^d]++;

                    if ((a^b^c^d) != 0) {
                        res++;
                    }

                    t++;
                }
            }
        }
    }

    for (auto p : m) {
        std::cout << p.first << ": " << p.second << std::endl;
    }

    std::cout << res << std::endl;
    std::cout << "total: "<< t << std::endl;
}

int main() {
    int a, b, c, d;

    std::cin >> a >> b >> c >> d;

    std::vector<int> v({a,b,c,d});
    std::sort(v.begin(), v.end());

    std::vector<std::vector<int>> M(10000, std::vector<int>());

    int z = 0;

    for (int a = 1; a <= v[2]; a++) {
        for (int b = a; b <= v[3]; b++) {
            int x = a ^ b;
            M[x].push_back(a);
        }
    }

    long total = 0;
    for (int a = 1; a <= v[0]; a++) {
        for (int b = a; b <= v[1]; b++) {
            int x = a ^ b;
            auto it = std::lower_bound(M[x].begin(), M[x].end(), b);
            z += std::distance(it, M[x].end());

            int q = v[3] - v[2] + 1;
            int r = v[3] - b + 1;
            int n = v[2] - b + 1;

            total += (((q+r)*n)/2);
        }
    }

    std::cout << (total - z) << std::endl;

    //brute_force_debug(a,b,c,d);
}
