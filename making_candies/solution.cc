#include <vector>
#include <iostream>
#include <map>



int main() {
    long m, w, p, n;

    std::cin >> m >> w >> p >> n;

    // solve it
    long c = m * w;
    long res = 1;

    while (c < n) {
        long x = c / p;
        c = c % p;

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

        c += m*w;

        std::cout << "m=" << m << ", w=" << w << " c=" << c << std::endl;
        res++;
    }

    std::cout << res << std::endl;
}
