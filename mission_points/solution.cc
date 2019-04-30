#include <bits/stdc++.h>

using namespace std;

struct City {
    int latitude;
    int longitude;
    int height;
    int point;
};


////////////////////////////////////////////////////////////////////////////////

template<typename T>
struct Node {
    int key;
    Node *left;
    Node *right;
    int height;
    T value;
};

template<typename T>
int height(Node<T> *N) {
    if (N == nullptr)
        return 0;

    return N->height;
}

template<typename T>
Node<T>* newNode(int key, T def) {
    auto* node = new Node<T>();
    node->key = key;
    node->left = nullptr;
    node->right = nullptr;
    node->height = 1; // new node is initially
    node->value = def;

    // added at leaf
    return(node);
}

template<typename T>
Node<T> *rightRotate(Node<T> *y) {
    Node<T> *x = y->left;
    Node<T> *T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    y->height = max(height(y->left),
                    height(y->right)) + 1;
    x->height = max(height(x->left),
                    height(x->right)) + 1;

    // Return new root
    return x;
}

template<typename T>
Node<T> *leftRotate(Node<T> *x) {
    Node<T> *y = x->right;
    Node<T> *T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    // Update heights
    x->height = max(height(x->left),
                    height(x->right)) + 1;
    y->height = max(height(y->left),
                    height(y->right)) + 1;

    // Return new root
    return y;
}

template<typename T>
int getBalance(Node<T> *N) {
    if (N == nullptr)
        return 0;
    return height(N->left) - height(N->right);
}

template<typename T, typename Functor>
Node<T>* insert(Node<T>* node, int key, T def, Functor&& f) {
    if (node == nullptr) {
        node = newNode<T>(key, def);
    }

    // apply function f to value
    node->value = f(node->value);

    if (key < node->key)
        node->left = insert(node->left, key, def, f);
    else if (key > node->key)
        node->right = insert(node->right, key, def, f);
    else // Equal keys are not allowed in BST
        return node;

    node->height = 1 + max(height(node->left),
                           height(node->right));

    int balance = getBalance<T>(node);

    // Left Left Case
    if (balance > 1 && key < node->left->key)
        return rightRotate(node);

    // Right Right Case
    if (balance < -1 && key > node->right->key)
        return leftRotate(node);

    // Left Right Case
    if (balance > 1 && key > node->left->key)
    {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Right Left Case
    if (balance < -1 && key < node->right->key)
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

////////////////////////////////////////////////////////////////////////////////

long get_max_y(Node<long> *node, int l, int r) {
    while (node != nullptr && l < node->key && r < node->key) {
        node = node->left;
    }

    while (node != nullptr && l > node->key && r > node->key) {
        node = node->right;
    }

    long result = 0;
    if (node == nullptr) {
        return result;
    }

    result = node->value;

    Node<long> *node_l = node->left;
    while (node_l != nullptr && node_l->key >= l) {
        if (node_l->value > result) {
            result = node_l->value;
        }
        node_l = node_l->left;
    }

    Node<long> *node_r = node->right;
    while (node_r != nullptr && node_r->key <= r) {
        if (node_r->value > result) {
            result = node_r->value;
        }
        node_r = node_r->right;
    }

    return result;
}

long get_max(Node<Node<long> *> *node, int xl, int xr, int yl, int yr) {
    while (node != nullptr && xl < node->key && xr < node->key) {
        node = node->left;
    }

    while (node != nullptr && xl > node->key && xr > node->key) {
        node = node->right;
    }

    long result = 0;
    if (node == nullptr) {
        return result;
    }

    result = get_max_y(node->value, yl, yr);

    Node<Node<long>*> *node_l = node->left;
    while (node_l != nullptr && node_l->key >= xl) {
        long l = get_max_y(node_l->value, yl, yr);
        if (l > result) {
            result = l;
        }
        node_l = node_l->left;
    }

    Node<Node<long>*> *node_r = node->right;
    while (node_r != nullptr && node_r->key <= xr) {
        long l = get_max_y(node_r->value, yl, yr);
        if (l > result) {
            result = l;
        }

        node_r = node_r->right;
    }
}

Node<Node<long>*> *update(Node<Node<long>*> *node, int x, int y, long value) {
    auto lambda_y = [&](long v2) {
        return max(value, v2);
    };

    auto lambda_x = [&](Node<long> *node) {
        return insert(node, y, 0L, lambda_y);
    };

    Node<long> *def = nullptr;

    return insert(node, x, def, lambda_x);
}

////////////////////////////////////////////////////////////////////////////////

void solve(int n, int d_lat, int d_long, vector<City>& cities) {
    sort(cities.begin(), cities.end(), [](const City& c1, const City& c2) {
        return c1.height > c2.height;
    });

    Node<Node<long>*> *range_tree = nullptr;

    long result = 0;

    for (auto &c : cities) {
        int x1 = max(0, c.latitude - d_lat);
        int y1 = max(0, c.longitude - d_long);
        int x2 = c.latitude + d_lat;
        int y2 = c.longitude + d_long;

        long max_points = get_max(range_tree, x1, x2, y1, y2);
        max_points += c.point;

        if (max_points > result) {
            result = max_points;
        }

        range_tree = update(range_tree, c.latitude, c.longitude, max_points);
    }

    cout << result << endl;

}

int main(int argc, char **argv) {
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