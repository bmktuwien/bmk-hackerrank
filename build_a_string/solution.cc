#include <algorithm>
#include <iostream>
#include <map>
#include <vector>
#include <set>
#include <random>


long build_brute2(int a, int b, const std::string& s, int i, std::vector<long>& cache) {
    long res = 0;

    if (i >= s.size()) {
        return 0;
    }

    if (cache[i] != -1) {
        return cache[i];
    }

    res = std::min(a,b) + build_brute2(a, b, s, i+1, cache);

    auto s1 = s.substr(0,i);

    int q = 2;
    while (s1.find(s.c_str()+i, 0, q) != std::string::npos) {
        long r = b + build_brute2(a, b, s, i+q, cache);
        if (r < res) {
            res = r;
        }

        q++;
    }

    cache[i] = res;


    return res;
}

long build_brute(int a, int b, std::string s1, std::string s2) {
    long res = 0;

    if (s2.empty()) {
        return 0;
    }

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

int main() {
    int t;
    std::cin >> t;

    while (t--) {
        int n, a, b;
        std::cin >> n >> a >> b;
        std::string input;
        std::cin >> input;

        std::vector<long> cache(input.size(),-1);


        //std::cout << build_brute(a,b,"",input) << std::endl;
        std::cout << build_brute2(a,b,input,0,cache) << std::endl;
    }
}
