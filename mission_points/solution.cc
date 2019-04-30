#include <bits/stdc++.h>

using namespace std;

struct City {
    int latitude;
    int longitude;
    int height;
    int point;
};


////////////////////////////////////////////////////////////////////////////////

template<typename T1, typename T2>
struct Node {
    int key;
    Node *left;
    Node *right;
    int height;
    T1 v1;
    T2 v2;
};

template<typename T1, typename T2>
int height(Node<T1,T2> *N) {
    if (N == nullptr)
        return 0;

    return N->height;
}

template<typename T1, typename T2>
Node<T1,T2>* newNode(int key, T1 def1, T2 def2) {
    auto* node = new Node<T1,T2>();
    node->key = key;
    node->left = nullptr;
    node->right = nullptr;
    node->height = 1; // new node is initially
    node->v1 = def1;
    node->v2 = def2;

    // added at leaf
    return(node);
}

template<typename T1,typename T2>
Node<T1,T2> *rightRotate(Node<T1,T2> *y) {
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

template<typename T1, typename T2>
Node<T1,T2> *leftRotate(Node<T1,T2> *x) {
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

template<typename T1, typename T2>
int getBalance(Node<T1,T2> *N) {
    if (N == nullptr)
        return 0;
    return height(N->left) - height(N->right);
}

template<typename T1, typename T2, typename Functor>
Node<T1,T2>* insert(Node<T1,T2>* node, int key, T1 def1, T2 def2, Functor f) {
    if (node == nullptr) {
        node = newNode<T1,T2>(key, def1, def2);
    }

    node->v2 = f(node->v2);

    if (key < node->key) {
        node->left = insert(node->left, key, def1, def2, f);
    } else if (key > node->key) {
        node->right = insert(node->right, key, def1, def2, f);
    } else {
        return node;
    }

    node->height = 1 + max(height(node->left),
                           height(node->right));

    int balance = getBalance(node);

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

long get_max_y(Node<long,long> *node, int l, int r) {
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

    result = node->v1;

    auto *node_l = node->left;
    while (node_l != nullptr) {
        if (node_l->key >= l) {
            long tmp = max(node_l->v1, node_l->right != nullptr ? node_l->right->v2 : 0L);

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
            long tmp = max(node_r->v1, node_r->left != nullptr ? node_r->left->v2 : 0L);

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

long get_max(Node<pair<int,long>, Node<long,long>*> *node, int xl, int xr, int yl, int yr) {

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

    if (yl <= node->v1.first && node->v1.first <= yr) {
        result = node->v1.second;
    }

    auto *node_l = node->left;
    while (node_l != nullptr) {
        if (node_l->key >= xl) {
            auto ptr = node_l->right != nullptr ? node_l->right->v2 : nullptr;
            long tmp = 0;
            if (yl <= node_l->v1.first && node_l->v1.first <= yr) {
                tmp = node_l->v1.second;
            }
            tmp = max(tmp, get_max_y(ptr, yl, yr));

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
            auto ptr = node_r->left != nullptr ? node_r->left->v2 : nullptr;
            long tmp = 0;
            if (yl <= node_r->v1.first && node_r->v1.first <= yr) {
                tmp = node_r->v1.second;
            }
            tmp = max(tmp,  get_max_y(ptr, yl, yr));

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

Node<pair<int,long>, Node<long,long>*> *update(Node<pair<int,long>, Node<long,long>*> *node, int x, int y, long value) {
    Node<long,long> *null_ptr = nullptr;

    auto f1 = [&value](long v) {
        return max(value, v);
    };

    auto f2 = [&](Node<long,long> *n) {
        return insert(n, y, value, 0L, f1);
    };


    return insert(node, x, make_pair(y,value), null_ptr, f2);
}

////////////////////////////////////////////////////////////////////////////////

struct Entry {
    int latitude;
    int longitude;
    long max_points;
};

void solve(int n, int d_lat, int d_long, vector<City>& cities) {
    sort(cities.begin(), cities.end(), [](const City& c1, const City& c2) {
        return c1.height > c2.height;
    });

    Node<pair<int,long>, Node<long,long>*> *range_tree = nullptr;

    long result = 0;
    //int cnt = 0;
    //vector<Entry> acc;

    for (auto &c : cities) {
        int x1 = max(0, c.latitude - d_lat);
        int y1 = max(0, c.longitude - d_long);
        int x2 = c.latitude + d_lat;
        int y2 = c.longitude + d_long;

        /*long max_points2 = 0;
        for (const Entry& e : acc) {
            if ((abs(e.latitude-c.latitude) <= d_lat) &&
                (abs(e.longitude-c.longitude) <= d_long) &&
                (e.max_points > max_points2)) {
                max_points2 = e.max_points;
            }
        }


        cout << "x1=" << x1 << " y1=" << y1 << " x2=" << x2 << " y2=" << y2 << " x=" << c.latitude << " y=" << c.longitude << endl;
        long max_points = max(0L, get_max(range_tree, x1, x2, y1, y2));
        cout << "maxpoints=" << max_points << endl;
        cout << "maxpoints2=" << max_points2 << endl;
        cout << "c=" << max_points+c.point << endl;
        cout << "-----------------------------------" << endl;*/

        long max_points = max(0L, get_max(range_tree, x1, x2, y1, y2));
        /*if (max_points != max_points2) {
            cout << "fuck!" << endl;
            get_max(range_tree, x1, x2, y1, y2);
            return;
        }*/
        max_points += c.point;

        if (max_points > result) {
            result = max_points;
        }

        //acc.push_back({c.latitude, c.longitude, max_points});
        range_tree = update(range_tree, c.latitude, c.longitude, max_points);

        //cnt++;
        //if (cnt > 100) {
        //    break;
        //}
    }

    cout << result << endl;


}

int main(int argc, char **argv) {
    //std::ifstream is("tests/input08.txt");

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