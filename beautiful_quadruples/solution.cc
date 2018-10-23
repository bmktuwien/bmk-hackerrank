#include <algorithm>
#include <vector>
#include <iostream>
#include <map>
#include <set>


int main() {
    int a, b, c, d;

    std::cin >> a >> b >> c >> d;

    std::vector<int> v({a,b,c,d});
    std::sort(v.begin(), v.end());

    int res = 0;

    for (int a = 1; a <= v[0]; a++) {
        for (int b = a; b <= v[1]; b++) {
            for (int c = b; c <= v[2]; c++) {
                for (int d = c; d <= v[3]; d++) {
                    if ((a^b^c^d) != 0) {
                        res++;
                    }
                }
            }
        }
    }

    std::cout << res << std::endl;
}
