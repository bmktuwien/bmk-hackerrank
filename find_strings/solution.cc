#include <algorithm>
#include <iostream>
#include <vector>
#include <map>

std::vector<std::pair<int,int>> calc_sa_stupid(const std::vector<std::string>& ss) {
    std::vector<std::pair<std::string,std::pair<int,int>>> v;

    for (size_t j = 0; j < ss.size(); j++) {
        for (size_t i = 0; i < ss[j].length(); i++) {
            v.push_back(std::make_pair(ss[j].substr(i), std::make_pair(j,i)));
        }
    }


    std::sort(v.begin(), v.end());

    std::vector<std::pair<int,int>> res;
    for (auto &p : v) {
        res.push_back(p.second);
    }

    return res;
}

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
        std::cout << "stage: " << H << std::endl;

        std::cout << "pos: ";
        for (size_t i = 0; i < pos.size(); i++) {
            std::cout << "(" << pos[i].first << "," << pos[i].second << "," << bh[i] << ")  ";
        }
        std::cout << std::endl;

        std::vector<int> count(pos.size(), 0);
        std::vector<bool> b2h(bh);

        for (size_t i = 0, j = 0; i < pos.size(); i++) {
            if (bh[i]) {
                j = i;
            }
            inv_pos[pos[i]] = j;
        }

        std::cout << "inv_pos: ";
        for (auto &x : inv_pos) {
            std::cout << "(" << x.first.first << "," << x.first.second << "->" << x.second << ")  ";
        }
        std::cout << std::endl;

        for (int i = pos.size() - H; i >= 0 && i < pos.size(); i++) {
            int q = inv_pos[std::make_pair(pos[i].first, i)];

            count[q] += 1;
        }

        int k = 0;
        int i = 0;

        while (i < pos.size()) {
            int j = k;
            i = j;
            std::vector<bool> btmp(pos.size(), false);

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


            k = i;
            i = j;

            do {
                auto t = std::make_pair(pos[i].first, pos[i].second - H);

                if (t.second >= 0) {
                    int q = inv_pos[t];

                    if (q+1 < pos.size() && btmp[q+1])  {
                        std::cout << "fuck: " << std::endl;
                        b2h[q+1] = false;
                    }
                }

                i++;
            } while (i < k);
        }

        std::cout << "inv_pos: ";
        for (auto &x : inv_pos) {
            std::cout << "(" << x.first.first << "," << x.first.second << "->" << x.second << ")  ";
        }
        std::cout << std::endl;

        bh = b2h;
        for (auto &x : inv_pos) {
            pos[x.second] = x.first;
        }

        H *= 2;
    }

    return pos;
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
    std::vector<std::string> inp;
    int n, k;

    std::cin >> n;

    while (n--) {
        std::string s;
        std::cin >> s;
        inp.push_back(s);
    }

    auto sa = calc_sa(inp);
    for (auto &p : sa) {
        std::cout << "(" << p.first << "," << p.second << ")  ";
    }
    std::cout << std::endl;

    auto sa2 = calc_sa_stupid(inp);
    for (auto &p : sa2) {
        std::cout << "(" << p.first << "," << p.second << ")  ";
    }
    std::cout << std::endl;

    //auto sa = calc_sa_stupid(inp);
    /*auto lcp = calc_lcp_stupid(inp, sa);

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

    solve(inp, k, sa, lcp);*/
}
