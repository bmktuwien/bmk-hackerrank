#include <algorithm>
#include <iostream>
#include <map>
#include <vector>
#include <set>
#include <random>

std::string random_string( size_t length )
{
    auto randchar = []() -> char
                        {
                            const char charset[] =
                                "abcdefghijklmnopqrstuvwxyz";
                            const size_t max_index = (sizeof(charset) - 1);
                            return charset[ rand() % max_index ];
                        };
    std::string str(length,0);
    std::generate_n( str.begin(), length, randchar );
    return str;
}

long build(int a, int b, std::string& s) {
    long res = 0;

    int c = b/a+1;
    res = a * std::min(c,(int)s.size());

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

long build_brute(int a, int b, std::string s1, std::string s2) {
    long res = 0;


    if (s2.empty()) {
        return 0;
    }

    std::cout << "s1=" << s1 << " s2=" << s2 << std::endl;
    res = a + build_brute(a, b, s1+s2[0], s2.substr(1));

    int q = 1;
    while (s1.find(s2.c_str(), 0, q) != std::string::npos) {
        auto sub = s2.substr(0, q);
        long r = b + build_brute(a, b, s1+sub, s2.substr(q));
        if (r < res) {
            res = r;
        }

        q++;
    }


    return res;
}

void find_bug() {
    while (true) {
        auto input = random_string(10);
        int a = 7890;
        int b = 7891;

        auto r1 = build_brute(a,b,"",input);
        auto r2 = build(a,b,input);

        if (r1 != r2) {
            std::cout << "found bug: " << input << std::endl;
        }
    }
}

int main() {
    int t;
    std::cin >> t;

    while (t--) {
        int n, a, b;
        std::cin >> n >> a >> b;
        std::string input;
        std::cin >> input;

        std::cout << build_brute(a,b,"",input) << std::endl;
        std::cout << build(a,b,input) << std::endl;
    }
}
