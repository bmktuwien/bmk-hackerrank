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
        int q = c;
        bool found = false;

        while (s2.find(s.c_str(), 0, q) != std::string::npos) {
            found = true;
            q++;
        }

        std::cout << "built=" << s2 << " rest=" << s << " fouund=" << found << std::endl;

        if (!found) {
            std::cout << "appending: " << s[0] << std::endl;
            s2.push_back(s[0]);
            s.erase(0, 1);

            res += a;
        } else {
            std::cout << "copying: " << s.substr(0,q-1) << std::endl;
            s2.append(s, 0, q-1);
            s.erase(0, q-1);

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
