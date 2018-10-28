#include <algorithm>
#include <iostream>
#include <map>
#include <vector>
#include <set>
#include <random>


long build_brute(int a, int b, const std::string& s, int i, std::vector<long>& cache) {
    long res = 0;

    if (i >= s.size()) {
        return 0;
    }

    if (cache[i] != -1) {
        return cache[i];
    }

    res = std::min(a,b) + build_brute(a, b, s, i+1, cache);

    auto s1 = s.substr(0,i);

    int q = 2;
    while (s1.find(s.c_str()+i, 0, q) != std::string::npos) {
        q++;
    }

    long r = b + build_brute(a, b, s, i+q-1, cache);
    if (r < res) {
        res = r;
    }

    cache[i] = res;


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

        std::cout << build_brute(a,b,input,0,cache) << std::endl;
    }
}
