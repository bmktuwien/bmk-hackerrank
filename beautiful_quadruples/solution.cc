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

    for (int a = 1; a <= v[0]; a++) {
        for (int b = a; b <= v[1]; b++) {
            for (int c = b; c <= v[2]; c++) {
                for (int d = c; d <= v[3]; d++) {
                    m[a^b^c^d]++;

                    if ((a^b^c^d) != 0) {
                        res++;
                    }
                }
            }
        }
    }

    for (auto p : m) {
        std::cout << p.first << ": " << p.second << std::endl;
    }

    std::cout << res << std::endl;
}

int main() {
    int a, b, c, d;

    std::cin >> a >> b >> c >> d;

    std::vector<int> v({a,b,c,d});
    std::sort(v.begin(), v.end());

    long total_cnt = 0;
    int z = 0;

    for (int a = 1; a <= v[0]; a++) {
        for (int b = a; b <= v[1]; b++) {
            for (int c = b; c <= v[2]; c++) {
                int x = a^b^c;

                if (x >= c && x <= v[3]) {
                    z++;
                }

                total_cnt += (v[3]-c+1);
            }
        }
    }

    std::cout << (total_cnt - z) << std::endl;

    //brute_force_debug(a,b,c,d);
}
