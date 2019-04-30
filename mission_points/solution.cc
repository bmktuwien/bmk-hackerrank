#include <bits/stdc++.h>

using namespace std;

struct City {
    int latitude;
    int longitude;
    int height;
    int point;
};


////////////////////////////////////////////////////////////////////////////////

struct NodeY {
    NodeY *left{nullptr};
    NodeY *right{nullptr};
    int height{1};
    int key{-1};
    long max{-1};
    long value{-1};
};

struct NodeX {
    NodeX *left{nullptr};
    NodeX *right{nullptr};
    int height{1};
    int key{-1};
    long y{-1};
    long value{-1};
    NodeY *yTree{nullptr};
};


template<typename Node>
int height(Node *N) {
    if (N == nullptr)
        return 0;

    return N->height;
}

template<typename Node>
Node *rightRotate(Node *y) {
    auto *x = y->left;
    auto *t2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = t2;

    // Update heights
    y->height = max(height(y->left),
                    height(y->right)) + 1;
    x->height = max(height(x->left),
                    height(x->right)) + 1;

    // Return new root
    return x;
}

template<typename Node>
Node *leftRotate(Node *x) {
    auto *y = x->right;
    auto *t2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = t2;

    // Update heights
    x->height = max(height(x->left),
                    height(x->right)) + 1;
    y->height = max(height(y->left),
                    height(y->right)) + 1;

    // Return new root
    return y;
}

template<typename Node>
int getBalance(Node *node) {
    if (node == nullptr)
        return 0;
    return height(node->left) - height(node->right);
}

NodeY* insertY(NodeY* node, int y, long value) {
    if (node == nullptr) {
        node = new NodeY();
        node->key = y;
        node->value = value;
        node->max = value;
        return node;
    }

    node->max = max(node->max, value);

    if (y < node->key) {
        node->left = insertY(node->left, y, value);
    } else if (y > node->key) {
        node->right = insertY(node->right, y, value);
    } else {
       return node;
    }

    node->height = 1 + max(height(node->left),
                           height(node->right));

    int balance = getBalance(node);

    // Left Left Case
    if (balance > 1 && y < node->left->key)
        return rightRotate(node);

    // Right Right Case
    if (balance < -1 && y > node->right->key)
        return leftRotate(node);

    // Left Right Case
    if (balance > 1 && y > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Right Left Case
    if (balance < -1 && y < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

NodeX* insertXPhase1(NodeX* node, int x, int y, long value) {
    if (node == nullptr) {
        node = new NodeX();
        node->key = x;
        node->y = y;
        node->value = value;
        return node;
    }

    if (x < node->key) {
        node->left = insertXPhase1(node->left, x, y, value);
    } else if (x > node->key) {
        node->right = insertXPhase1(node->right, x, y, value);
    } else {
        return node;
    }

    node->height = 1 + max(height(node->left),
                           height(node->right));

    int balance = getBalance(node);

    // Left Left Case
    if (balance > 1 && x < node->left->key)
        return rightRotate(node);

    // Right Right Case
    if (balance < -1 && x > node->right->key)
        return leftRotate(node);

    // Left Right Case
    if (balance > 1 && x > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Right Left Case
    if (balance < -1 && x < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

void insertXPhase2(NodeX* node, int x, int y, long value) {
    while (node != nullptr) {
        node->yTree = insertY(node->yTree, y, value);

        if (x < node->key) {
            node = node->left;
        } else if (x > node->key) {
            node = node->right;
        } else {
            return;
        }
    }
}

////////////////////////////////////////////////////////////////////////////////

long get_max_y(NodeY *node, int l, int r) {
    long result = 0;
    while (node != nullptr) {
        if (node->key < l) {
            node = node->right;
        } else if (node->key > r) {
            node = node->left;
        } else {
            break;
        }
    }

    if (node == nullptr) {
        return result;
    }

    result = node->value;

    auto *node_l = node->left;
    while (node_l != nullptr) {
        if (node_l->key >= l) {
            long tmp = max(node_l->value, node_l->right != nullptr ? node_l->right->max : 0L);

            if (tmp > result) {
                result = tmp;
            }
        }

        if (node_l->key < l) {
            node_l = node_l->right;
        } else if (node_l->key > l) {
            node_l = node_l->left;
        } else {
            break;
        }
    }

    auto *node_r = node->right;
    while (node_r != nullptr) {
        if (node_r->key <= r) {
            long tmp = max(node_r->value, node_r->left != nullptr ? node_r->left->max : 0L);

            if (tmp > result) {
                result = tmp;
            }
        }

        if (node_r->key < r) {
            node_r = node_r->right;
        } else if (node_r->key > r) {
            node_r = node_r->left;
        } else {
            break;
        }
    }

    return result;
}

long get_max(NodeX *node, int xl, int xr, int yl, int yr) {

    long result = 0;
    while (node != nullptr) {
        if (node->key < xl) {
            node = node->right;
        } else if (node->key > xr) {
            node = node->left;
        } else {
            break;
        }
    }

    if (node == nullptr) {
        return result;
    }

    if (yl <= node->y && node->y <= yr) {
        result = node->value;
    }

    auto *node_l = node->left;
    while (node_l != nullptr) {
        if (node_l->key >= xl) {
            auto ptr = node_l->right != nullptr ? node_l->right->yTree : nullptr;
            long tmp = get_max_y(ptr, yl, yr);
            if (yl <= node_l->y && node_l->y <= yr && node_l->value > tmp) {
                tmp = node_l->value;
            }

            if (tmp > result) {
                result = tmp;
            }
        }

        if (node_l->key < xl) {
            node_l = node_l->right;
        } else if (node_l->key > xl) {
            node_l = node_l->left;
        } else {
            break;
        }
    }

    auto *node_r = node->right;
    while (node_r != nullptr ) {
        if (node_r->key <= xr) {
            auto ptr = node_r->left != nullptr ? node_r->left->yTree : nullptr;
            long tmp = get_max_y(ptr, yl, yr);
            if (yl <= node_r->y && node_r->y <= yr && node_r->value > tmp) {
                tmp = node_r->value;
            }

            if (tmp > result) {
                result = tmp;
            }
        }

        if (node_r->key < xr) {
            node_r = node_r->right;
        } else if (node_r->key > xr) {
            node_r = node_r->left;
        } else {
            break;
        }
    }

    return result;
}

void updateY(NodeY* node, int y, long value) {
    while (node != nullptr) {
        node->max = max(node->max, value);

        if (y < node->key) {
            node = node->left;
        } else if (y > node->key) {
            node = node->right;
        } else {
            node->value = value;
            return;
        }
    }
}

void updateX(NodeX* node, int x, int y, long value) {
    while (node != nullptr) {
        updateY(node->yTree, y, value);

        if (x < node->key) {
            node = node->left;
        } else if (x > node->key) {
            node = node->right;
        } else {
            node->y = y;
            node->value = value;
            return;
        }
    }
}

////////////////////////////////////////////////////////////////////////////////

void solve(int n, int d_lat, int d_long, vector<City>& cities) {
    sort(cities.begin(), cities.end(), [](const City& c1, const City& c2) {
        return c1.height > c2.height;
    });

    NodeX *range_tree = nullptr;
    for (auto &c : cities) {
        range_tree = insertXPhase1(range_tree, c.latitude, c.longitude, 0);
    }
    for (auto &c : cities) {
        insertXPhase2(range_tree, c.latitude, c.longitude, 0);
    }


    long result = 0;

    for (auto &c : cities) {
        int x1 = max(0, c.latitude - d_lat);
        int y1 = max(0, c.longitude - d_long);
        int x2 = c.latitude + d_lat;
        int y2 = c.longitude + d_long;


        long max_points = max(0L, get_max(range_tree, x1, x2, y1, y2));
        max_points += c.point;

        if (max_points > result) {
            result = max_points;
        }

        updateX(range_tree, c.latitude, c.longitude, max_points);

    }

    cout << result << endl;


}

int main(int argc, char **argv) {
    //std::ifstream is("tests/input09.txt");

    int n, d_lat, d_long;
    cin >> n >> d_lat >> d_long;

    vector<City> cities;
    for (int i = 0; i < n; i++) {
        int lat, lng, height, point;
        cin >> lat >> lng >> height >> point;
        cities.push_back({lat, lng, height, point});
    }

    solve(n, d_lat, d_long, cities);
}