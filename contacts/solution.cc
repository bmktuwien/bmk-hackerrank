#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>

class Trie {
    const static int ALPHABET_SIZE = 26;

public:
    Trie() {
        _root = newNode();
    }

    Trie(const Trie&) = delete;

    Trie &operator=(const Trie&) = delete;

    void insert(const std::string &key) {
        auto n = _root;

        for (int i = 0; i < key.length(); i++) {
            int index = key[i] - 'a';

            if (n->children[index] == nullptr) {
                n->children[index] = newNode();
            }

            n->children_cnt++;
            n = n->children[index];
        }

        n->end_word = true;
    }

   int search(const std::string &key) {
        auto n = _root;

        for (int i = 0; i < key.length(); i++) {
            int index = key[i] - 'a';

            if (n->children[index] == nullptr) {
                return 0;
            }


            n = n->children[index];
        }

        int cnt = 0;
        if (n != nullptr) {
            cnt = n->children_cnt;
            if (n->end_word) {
                cnt++;
            }
        }

        return cnt;
    }

private:
    struct Node {
        Node *children[ALPHABET_SIZE];
        bool end_word{false};
        int children_cnt{0};
    };

    Node *_root{nullptr};

    Node *newNode() {
        auto n = new Node;

        for (int i = 0; i < ALPHABET_SIZE; i++) {
            n->children[i] = nullptr;
        }

        return n;
    }
};


int main() {
    int n;
    std::cin >> n;

    Trie trie;

    while (n--) {
        std::string cmd;
        std::string param;
        std::cin >> cmd >> param;

        if (cmd == "add") {
            trie.insert(param);
        } else if (cmd == "find") {
            auto x = trie.search(param);
            std::cout << x << std::endl;
        }
    }
}
