#include <vector>
#include <iostream>
#include <map>


uint64_t next_rate(uint64_t &m, uint64_t &w, uint64_t x) {
    if (m < w) {
        long y =  (w-m < x ? w-m : x);
        m += y;
        x -= y;
    }

    if (w < m) {
        long y =  (m-w < x ? m-w : x);
        w += y;
        x -= y;
    }

    m += (x/2);
    w += (x/2);

    if (x % 2 == 1) {
        m++;
    }


    return m*w;
}

int main() {
    uint64_t m, w, p, n;

    std::cin >> m >> w >> p >> n;

    // solve it
    uint64_t r = m * w;

    if (m != 0 && r / m != w) {
        // overflow handling
        std::cout << 1 << std::endl;
        return 0;
    }

    uint64_t res = 1 + (n-1)/r;
    uint64_t c = r;
    uint64_t k = 1;

    while (res > 1) {
        if (c < p) {
            uint64_t t = (p-c+r-1)/r;
            c += (r*t);
            k += t;
        }

        uint64_t x = c / p;
        r = next_rate(m,w,x);
        c = c % p;

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
