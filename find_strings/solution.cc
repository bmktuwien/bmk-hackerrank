#include <algorithm>
#include <iostream>
#include <vector>

std::vector<int> calc_sa_stupid(const std::string& s) {
    std::vector<std::pair<std::string,int>> v;

    for (size_t i = 0; i < s.length(); i++) {
        v.push_back(std::make_pair(s.substr(i), i));
    }

    std::sort(v.begin(), v.end());

    std::vector<int> res;
    for (auto &p : v) {
        res.push_back(p.second);
    }

    return res;
}

std::vector<int> calc_lcp_stupid(const std::string& s, const std::vector<int>& sa) {
    std::vector<int> res{0};

    for (int i = 0; i < sa.size()-1; i++) {
        auto s1{s.substr(sa[i])};
        auto s2{s.substr(sa[i+1])};

        int c = 0;
        int q = 0;
        int r = 0;
        while (q < s1.size() && r < s2.size() && s1[q] == s2[q]) {
            q++;
            r++;
            c++;
        }

        res.push_back(c);
    }

    return res;
}

void solve(const std::string& input, int k, const std::vector<int>& sa, const std::vector<int> &lcp) {
    int cnt = 0;

    for (size_t i = 0; i < sa.size(); i++) {
        int m = input.size() - sa[i] - 1;
        int p = m - lcp[i] + 1;

        if (cnt + p >= k) {
            std::cout << input.substr(sa[i],lcp[i]+k-cnt) << std::endl;
            return;
        }

        cnt += p;
    }
}

int main() {
    std::string inp;
    int k;

    std::cin >> inp;
    std::cin >> k;

    auto sa = calc_sa_stupid(inp);
    auto lcp = calc_lcp_stupid(inp, sa);

    std::cout << "sa: ";
    for (auto i : sa) {
        std::cout << i << ", ";
    }
    std::cout << std::endl;

    std::cout << "lcp: ";
    for (auto i : lcp) {
        std::cout << i << ", ";
    }
    std::cout << std::endl;

    solve(inp, k, sa, lcp);
}
