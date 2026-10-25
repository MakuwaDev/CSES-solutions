#include <iostream>
#include <vector>
#include <bit>

class PersistentTree {
public:
    class ArrayProxy {
        public:
            ArrayProxy(PersistentTree& tree, std::size_t k) : tree(tree), k(k) {}

            void update(std::size_t pos, std::size_t val) {
                tree.roots.at(k) = tree.update_impl(tree.roots.at(k), 1, tree.size, pos, val);
            }

            std::size_t query(std::size_t l, std::size_t r) const {
                return tree.query_impl(tree.roots.at(k), 1, tree.size, l, r);
            }
            
            ArrayProxy clone() {
                tree.roots.push_back(tree.roots.at(k));
                std::size_t new_k = tree.roots.size() - 1;
                return ArrayProxy(tree, new_k);
            }

        private:
            PersistentTree& tree;
            std::size_t k;
    };

    class ConstArrayProxy {        
        public:
            ConstArrayProxy(PersistentTree const& tree, std::size_t k) : tree(tree), k(k) {}

            std::size_t query(std::size_t l, std::size_t r) const {
                return tree.query_impl(tree.roots.at(k), 1, tree.size, l, r);
            }

        private:
            PersistentTree const& tree;
            std::size_t k;
    };

    PersistentTree(std::vector<std::size_t> const& original) {
        size = original.size() - 1;
        tree.push_back({0, 0, 0});
        roots.push_back(0);
        roots.push_back(build(original, 1, size));
    }

    ArrayProxy operator[](std::size_t k) {
        return ArrayProxy(*this, k);
    }

    ConstArrayProxy operator[](std::size_t k) const {
        return ConstArrayProxy(*this, k);
    }

    void copy_array(std::size_t k) {
        roots.push_back(roots[k]);
    }

private:
    struct Node {
        std::size_t sum{0};
        std::size_t left{0};
        std::size_t right{0};

        Node(std::size_t s = 0, std::size_t l = 0, std::size_t r = 0) 
            : sum(s), left(l), right(r) {}
    };

    std::vector<Node> tree;
    std::vector<std::size_t> roots;

    std::size_t size;

    std::size_t create_node(Node data = Node()) {
        tree.push_back(data);
        return tree.size() - 1;
    }

    std::size_t build(std::vector<std::size_t> const& arr, std::size_t l, std::size_t r) {
        std::size_t id = create_node();

        if (l == r) {
            tree[id].sum = arr[l];
            return id;
        }

        std::size_t mid = l + (r - l) / 2;
        std::size_t left = build(arr, l, mid);
        std::size_t right = build(arr, mid + 1, r);

        tree[id].left = left;
        tree[id].right = right;
        tree[id].sum = tree[left].sum + tree[right].sum;

        return id;
    }

    std::size_t query_impl(std::size_t id, std::size_t l, std::size_t r, std::size_t ql, std::size_t qr) const {
        if (!id || ql > r || qr < l) {
            return 0;
        } else if (ql <= l && r <= qr) {
            return tree[id].sum;
        }

        std::size_t mid = l + (r - l) / 2;
        return query_impl(tree[id].left, l, mid, ql, qr) + query_impl(tree[id].right, mid + 1, r, ql, qr);
    }

    std::size_t update_impl(std::size_t prev_id, std::size_t l, std::size_t r, std::size_t pos, std::size_t val) {
        Node current = tree[prev_id];
        std::size_t id = create_node(current);

        if (l == r) {
            tree[id].sum = val;
            return id;
        }

        std::size_t mid = l + (r - l) / 2;
        if (pos <= mid) {
            std::size_t new_left = update_impl(tree[prev_id].left, l, mid, pos, val);
            tree[id].left = new_left;
        } else {
            std::size_t new_right = update_impl(tree[prev_id].right, mid + 1, r, pos, val);
            tree[id].right = new_right;
        }

        tree[id].sum = tree[tree[id].left].sum + tree[tree[id].right].sum;
        return id;
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::vector<std::size_t> original;
    std::size_t n, q, a, b, k;
    char c;

    std::cin >> n >> q;

    original.resize(n + 1);

    for (std::size_t i = 1; i <= n; ++i) {
        std::cin >> original[i];
    }

    PersistentTree arrays(original);

    while (q--) {
        std::cin >> c >> k;

        if (c == '1') {
            std::cin >> a >> b;
            arrays[k].update(a, b);
        } else if (c == '2') {
            std::cin >> a >> b;
            std::cout << arrays[k].query(a, b) << "\n";
        } else {
            arrays.copy_array(k);
        }
    }

    return 0;
}