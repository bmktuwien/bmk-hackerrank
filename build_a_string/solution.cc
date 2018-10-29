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

    int q = 0;
    for (int k = 0; k < i; k++) {
        int t = 0;
        int r = k;

        while ((r < i) && ((i+t) < s.size()) && (s[i+t] == s[r])) {
            r++;
            t++;
        }

        if (t > q) {
            q = t;
        }
    }
    //std::cout << "q=" << q << "i=" << i << std::endl;

    if (q > 1) {
        long r = b + build_brute(a, b, s, i+q, cache);
        if (r < res) {
            res = r;
        }
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
