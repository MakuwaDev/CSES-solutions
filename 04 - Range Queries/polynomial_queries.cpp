#include <iostream>
#include <vector>
#include <array>
#include <numeric>

constexpr std::size_t INF = std::numeric_limits<std::size_t>::max();
constexpr std::size_t MAXN = 2e5 + 5;

constexpr std::size_t calculate_tree_size(std::size_t maxn) {
    std::size_t res = 1;

    while (res < maxn) {
        res <<= 1;
    }

    return res;
}

constexpr std::size_t TREESIZE = calculate_tree_size(MAXN);

namespace core {

struct lazy {
    std::size_t start;
    std::size_t step;
};

} // namespace core

struct node {
    std::size_t val;
    std::size_t left;
    std::size_t right;
    core::lazy lazy;
};

std::array<node, 2 * TREESIZE> tree;

void init(std::vector<std::size_t> const& arr) {
    for (std::size_t i = 0; i < arr.size(); ++i) {
        tree[TREESIZE + i].val = arr[i];
        tree[TREESIZE + i].left = tree[TREESIZE + i].right = TREESIZE + i;
    }

    for (std::size_t i = TREESIZE + arr.size(); i < 2 * TREESIZE; ++i) {
        tree[i].left = tree[i].right = i;
    }

    for (std::size_t i = TREESIZE - 1; i > 0; --i) {
        tree[i].val = tree[2 * i].val + tree[2 * i + 1].val;
        tree[i].left = tree[2 * i].left;
        tree[i].right = tree[2 * i + 1].right;
    }
}

void push(std::size_t id) {
    std::size_t len = tree[id].right - tree[id].left + 1;
    auto& start = tree[id].lazy.start;
    auto& step = tree[id].lazy.step;

    if (start == 0 && step == 0) {
        return;
    }

    tree[id].val += (start * len) + (step * (len * (len - 1)) / 2);

    if (id < TREESIZE) {
        tree[2 * id].lazy.start += start;
        tree[2 * id].lazy.step += step;

        tree[2 * id + 1].lazy.start += (start + len * step / 2);
        tree[2 * id + 1].lazy.step += step;
    }

    tree[id].lazy = {0, 0};
}

std::size_t read(std::size_t id, std::size_t first, std::size_t last) {
    push(id);

    if (tree[id].left > last || tree[id].right < first) {
        return 0;
    } else {
        if (tree[id].left >= first && tree[id].right <= last) {
            return tree[id].val;
        } else {
            return read(2 * id, first, last) + read(2 * id + 1, first, last);
        }
    }
}

void update(std::size_t first, std::size_t last, std::size_t id) {
    push(id);

    if (tree[id].left > last || tree[id].right < first) {
        return;
    } else {
        if (tree[id].left >= first && tree[id].right <= last) {
            tree[id].lazy.start += (tree[id].left - first + 1);
            ++tree[id].lazy.step;

            push(id);
        } else {
            update(first, last, 2 * id);
            update(first, last, 2 * id + 1);

            tree[id].val = tree[2 * id].val + tree[2 * id + 1].val;
        }
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::size_t n, q, a, b;
    char t;
    std::vector<std::size_t> arr;
    
    std::cin >> n >> q;
    arr.resize(n);

    for (auto& x : arr) {
        std::cin >> x;
    }

    init(arr);

    while (q--) {
        std::cin >> t >> a >> b;

        if (t == '1') {
            update(a + TREESIZE - 1, b + TREESIZE - 1, 1);
        } else {
            std::cout << read(1, a + TREESIZE - 1, b + TREESIZE - 1) << "\n";
        }
    }

    return 0;
}