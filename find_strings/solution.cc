#include <algorithm>
#include <iostream>
#include <vector>
#include <map>


std::vector<std::pair<int,int>> calc_sa(const std::vector<std::string>& ss) {
    std::vector<std::vector<std::pair<int,int>>> tmp(26);
    size_t n = 0;
    for (size_t i = 0; i < ss.size(); i++) {
        if (ss[i].length() > n) {
            n = ss[i].length();
        }

        for (size_t j = 0; j < ss[i].length(); j++) {
            tmp[ss[i][j] - 'a'].push_back(std::make_pair(i,j));
        }
    }

    // initialize pos
    std::vector<std::pair<int,int>> pos;
    std::vector<bool> bh;
    for (auto &v1 : tmp) {
        bool b = true;
        for (auto &p: v1) {
            pos.push_back(p);
            bh.push_back(b);
            b = false;
        }
    }

    // initialze inv_pos
    std::map<std::pair<int,int>,int> inv_pos;
    for (size_t i = 0; i < pos.size(); i++) {
        inv_pos[pos[i]] = i;
    }

    int H = 1;

    while (H <= n) {
        std::vector<int> count(pos.size(), 0);
        std::vector<bool> b2h(bh);
        std::vector<bool> btmp(pos.size(), false);

        for (size_t i = 0, j = 0; i < pos.size(); i++) {
            if (bh[i]) {
                j = i;
            }
            inv_pos[pos[i]] = j;
        }

        // process incomplete suffixes first
        for (size_t j = 0; j < ss.size(); j++) {
            for (int i = std::max<int>(ss[j].size()-H,0); i < ss[j].size(); i++) {
                auto t = std::make_pair(j, i);
                int q = inv_pos[t];
                count[q] += 1;
                inv_pos[t] += (count[q] - 1);
                b2h[q] = true;
            }
        }

        int k = 0;
        int i = 0;

        while (i < pos.size()) {
            int j = k;
            i = j;

            // first loop marks the suffixes which are moved
            do {
                auto t = std::make_pair(pos[i].first, pos[i].second - H);

                if (t.second >= 0) {
                    int q = inv_pos[t];

                    count[q] += 1;
                    inv_pos[t] += (count[q] - 1);
                    b2h[inv_pos[t]] = true;
                    btmp[inv_pos[t]] = true;
                }

                i++;
            } while (i < pos.size() && !bh[i]);


            // second loop marks the H buckets correctly
            k = i;
            i = j;
            do {
                auto t = std::make_pair(pos[i].first, pos[i].second - H);

                if (t.second >= 0) {
                    int q = inv_pos[t];

                    if (q+1 < pos.size() && btmp[q+1] && !bh[q+1])  {
                        b2h[q+1] = false;
                    }
                }

                i++;
            } while (i < k);


            // finally cleanup the btmp
            k = i;
            i = j;
            do {
                auto t = std::make_pair(pos[i].first, pos[i].second - H);

                if (t.second >= 0) {
                    btmp[inv_pos[t]] = false;
                }

                i++;
            } while (i < k);
        }


        bh = b2h;
        for (auto &x : inv_pos) {
            pos[x.second] = x.first;
        }

        H *= 2;
    }

    return pos;
}

std::vector<int> calc_lcp(const std::vector<std::string>& ss,
                          const std::vector<std::pair<int,int>>& sa) {
    std::map<std::pair<int,int>,int> res;
    std::map<std::pair<int,int>,std::pair<int,int>> C;

    for (int i = 1; i < sa.size(); i++) {
        C[sa[i]] = sa[i-1];
    }

    for (int j = 0; j < ss.size(); j++) {
        int l = 0;

        for (int i = 0; i < ss[j].size(); i++) {
            auto p = std::make_pair(j,i);

            if (C.find(p) != C.end()) {
                auto cp = C[p];

                while (i+l < ss[j].size() && cp.second+l < ss[cp.first].size() &&
                       ss[j][i+l] == ss[cp.first][cp.second+l]) {
                    l++;
                }

                res[std::make_pair(j,i)] = l;

                l = std::max(l-1, 0);
            } else {
                res[std::make_pair(j,i)] = 0;
                l = 0;
            }
        }
    }

    std::vector<int> lcp(sa.size());
    for (int i = 0; i < sa.size(); i++) {
        lcp[i] = res[sa[i]];
    }

    return lcp;
}

void solve(const std::vector<std::string>& ss, int k,
           const std::vector<std::pair<int,int>>& sa, const std::vector<int> &lcp) {
    int cnt = 0;

    for (size_t i = 0; i < sa.size(); i++) {
        auto suf = sa[i];
        int m = ss[suf.first].size() - suf.second - 1;
        int p = m - lcp[i] + 1;

        if (cnt + p >= k) {
            std::cout << ss[suf.first].substr(suf.second,lcp[i]+k-cnt) << std::endl;
            return;
        }

        cnt += p;
    }

    std::cout << "INVALID" << std::endl;
}

int main() {
    std::vector<std::string> inp;
    int n;

    std::cin >> n;

    while (n--) {
        std::string s;
        std::cin >> s;
        inp.push_back(s);
    }

    auto sa = calc_sa(inp);
    auto lcp = calc_lcp(inp, sa);

    int q;
    std::cin >> q;

    while (q--) {
        int k;
        std::cin >> k;

        solve(inp, k, sa, lcp);
    }
}
