#include <iostream>
#include <vector>

class Tree {
public:
    Tree(std::vector<std::size_t> const& t) {
        treesize = calculate_tree_size(t.size());
        size = t.size();
        tree.resize(2 * treesize);

        for (std::size_t i = 0; i < size; ++i) {
            tree[treesize + i].val = t[i];
        }

        for (std::size_t i = treesize; i < 2 * treesize; ++i) {
            tree[i].lazy = {Op::Nop, 0};
            tree[i].left = tree[i].right = i;
        }

        for (std::size_t i = treesize - 1; i > 0; --i) {
            tree[i].left = tree[2 * i].left;
            tree[i].right = tree[2 * i + 1].right;
            tree[i].lazy = {Op::Nop, 0};
            tree[i].val = tree[2 * i].val + tree[2 * i + 1].val;
        }
    }

    void set(std::size_t first, std::size_t last, std::size_t val) {
        update_impl(first + treesize, last + treesize, 1, {Op::Set, val});
    }

    void add(std::size_t first, std::size_t last, std::size_t val) {
        update_impl(first + treesize, last + treesize, 1, {Op::Add, val});
    }

    std::size_t read(std::size_t first, std::size_t last) {
        return read_impl(1, first + treesize, last + treesize);
    }

private:
    enum class Op {
        Set,
        Add,
        Nop,
    };

    struct Lazy {
        Op type;
        std::size_t val; 
    };

    struct Node {
        std::size_t val;
        std::size_t left;
        std::size_t right;
        Lazy lazy;
    };

    std::vector<Node> tree;
    std::size_t treesize;
    std::size_t size;

    void push(std::size_t id) {
        if (tree[id].lazy.type == Op::Nop || id >= treesize) {
            return;
        }

        for (std::size_t child = 2 * id; child <= 2 * id + 1; ++child) {
            if (tree[id].lazy.type == Op::Set) {
                tree[child].val = (tree[child].right - tree[child].left + 1) * tree[id].lazy.val;
                tree[child].lazy = tree[id].lazy;
            } else {
                tree[child].val += (tree[child].right - tree[child].left + 1) * tree[id].lazy.val;
                tree[child].lazy.val += tree[id].lazy.val;

                if (tree[child].lazy.type == Op::Nop) {
                    tree[child].lazy.type = Op::Add;
                }
            }
        }

        tree[id].lazy = {Op::Nop, 0};
    }

    std::size_t calculate_tree_size(std::size_t n) {
        std::size_t res = 1;

        while (res < n) {
            res <<= 1;
        }

        return res;
    }

    std::size_t read_impl(std::size_t id, std::size_t first, std::size_t last) {
        if (tree[id].left > last || tree[id].right < first) {
            return 0;
        } else if (tree[id].left >= first && tree[id].right <= last) {
            return tree[id].val;
        } else {
            push(id);
            return read_impl(2 * id, first, last) + read_impl(2 * id + 1, first, last);
        }
    }

    void update_impl(std::size_t first, std::size_t last, std::size_t id, Lazy lazy) {
        if (tree[id].left > last || tree[id].right < first) {
            return;
        } else if (tree[id].left >= first && tree[id].right <= last) {
            if (lazy.type == Op::Set) {
                tree[id].val = (tree[id].right - tree[id].left + 1) * lazy.val;
                tree[id].lazy = lazy;
            } else {
                tree[id].val += (tree[id].right - tree[id].left + 1) * lazy.val;
                tree[id].lazy.val += lazy.val;

                if (tree[id].lazy.type == Op::Nop) {
                    tree[id].lazy.type = Op::Add;
                }
            }
        } else {
            push(id);

            update_impl(first, last, 2 * id, lazy);
            update_impl(first, last, 2 * id + 1, lazy);

            tree[id].val = tree[2 * id].val + tree[2 * id + 1].val;
        }
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::size_t n, q, a, b, x;
    char c;
    std::vector<std::size_t> t;

    std::cin >> n >> q;
    t.resize(n);

    for (auto& v : t) {
        std::cin >> v;
    }

    Tree tree(t);

    while (q--) {
        std::cin >> c >> a >> b;

        --a;
        --b;

        if (c == '3') {
            std::cout << tree.read(a, b) << "\n";
        } else {
            std::cin >> x;

            if (c == '1') {
                tree.add(a, b, x);
            } else {
                tree.set(a, b, x);
            }
        }
    }

    return 0;
}