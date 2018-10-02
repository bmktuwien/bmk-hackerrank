#include <vector>
#include <iostream>

void count_anagrams(const std::string& inp) {
    auto l = inp.length();

    for (auto w = 0; w < l-1; w++) {
        for (auto i = 0; i+w < l; i++) {
            std::cout << i << " " << i+w << ", ";
        }

        std::cout << std::endl;
    }
}

int main() {
    int q;

    std::cin >> q;

    while (q--) {
        std::string s;
        std::cin >> s;

        count_anagrams(s);
    }
}