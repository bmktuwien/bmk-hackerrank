#include <vector>
#include <iostream>
#include <map>


uint64_t next_rate(uint64_t *m, uint64_t *w) {
    if (*m < *w) {
        (*m)++;
    } else {
        (*w)++;
    }

    return (*m)*(*w);
}

int main() {
    uint64_t m, w, p, n;

    std::cin >> m >> w >> p >> n;

    // solve it
    uint64_t r = m * w;

    std::cout << r << std::endl;

    uint64_t res = 1 + (n-1)/r;

    uint64_t c = r;
    uint64_t k = 1;

    while (res > 1) {
        if (c < p) {
            uint64_t t = (p-c+r-1)/r;
            c += (r*t);
            k += t;
        }

        r = next_rate(&m,&w);
        c -= p;

        uint64_t res1 = k + (n-c+r-1)/r;

        std::cout << "r=" << r << " c=" << c << " k=" << k << " res=" << res << " res1=" << res1 << std::endl;

        if (res1 <= res) {
            res = res1;
        } else {
            break;
        }
    }

    std::cout << res << std::endl;
}
