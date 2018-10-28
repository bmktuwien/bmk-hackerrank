#include <algorithm>
#include <iostream>
#include <map>
#include <vector>
#include <set>

long build(int a, int b, std::string& s) {
    long res = 0;

    int c = b/a+1;
    res = a*c;

    std::string s2 = s.substr(0, c);
    s.erase(0, c);

    while (!s.empty()) {
        auto p = s2.find(s, c);
        if (p == std::string::npos) {
            s2.push_back(s[0]);
            s.erase(0, 1);

            res += a;
        } else {
            s2.append(s, c);
            s.erase(0, c);

            res += b;
        }
    }

    return res;
}

int main() {
    int t;
    std::cin >> t;

    while (t--) {
        int n, a, b;
        std::cin >> n >> a >> b;
        std::string input;
        std::cin >> input;

        std::cout << build(a,b,input) << std::endl;
    }
}
