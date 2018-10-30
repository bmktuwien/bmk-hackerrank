#include <algorithm>
#include <iostream>
#include <map>
#include <vector>
#include <set>
#include <random>


long build_brute(int a, int b, const std::string& s, int i, std::vector<long>& cache, const std::vector<int> &qs) {
    long res = 0;

    if (i >= s.size()) {
        return 0;
    }

    if (cache[i] != -1) {
        return cache[i];
    }

    res = std::min(a,b) + build_brute(a, b, s, i+1, cache, qs);

    if (qs[i] > 1) {
        long r = b + build_brute(a, b, s, i+qs[i], cache, qs);
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

        std::vector<std::vector<int>> indexes(26);
        for (int i = 0; i < input.size(); i++) {
            indexes[input[i]-'a'].push_back(i);
        }

        std::vector<int> qs(input.size());

        std::vector<int> v(input.size());
        for (int i = input.size()-1; i > 0; i--) {
            std::vector<int> v2(input.size());
            int q = 0;

            for (auto j : indexes[input[i]-'a']) {
                if (j >= i) {
                    break;
                }

                if ((j > 0) && (input[j-1] == input[i-1])) {
                    int l = std::min(i-j-1, v[j]+1);
                    v2[j-1] = l;

                    if (l > q) {
                        q = l;
                    }
                }


                if (q < v[j]+1) {
                    q = v[j]+1;
                }
            }

            qs[i] = q;
            v = std::move(v2);
        }

        std::vector<long> cache(input.size(),-1);
        std::cout << build_brute(a,b,input,0,cache,qs) << std::endl;
    }
}
