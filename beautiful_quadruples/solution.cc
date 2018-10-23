#include <algorithm>
#include <vector>
#include <iostream>
#include <map>


int main() {
    int a, b, c, d;

    std::cin >> a >> b >> c >> d;

    std::vector<int> v({a,b,c,d});
    std::sort(v.begin(), v.end());

    for (int a = 1; a <= v[0]; a++) {
        for (int b = a; b <= v[1]; b++) {
            std::cout << (a^b) << std::endl;
        }
    }
}
