#include <iostream>
#include <vector>
#include <array>
#include <numeric>
#include <cstdint>

constexpr std::size_t MAXN = 2e5 + 5;

constexpr std::size_t calculate_tree_size(std::size_t maxn) {
    std::size_t res = 1;

    while (res < maxn) {
        res <<= 1;
    }

    return res;
}

constexpr std::size_t TREESIZE = calculate_tree_size(MAXN);

struct node {
    int64_t best;
    int64_t sum;
    int64_t start;
    int64_t end;
};

std::array<node, 2 * TREESIZE> tree;

void tree_init(std::vector<int64_t> const& arr) {
    for (std::size_t i = 0; i < arr.size(); ++i) {
        tree[TREESIZE + i].sum = arr[i];
        tree[TREESIZE + i].start = std::max(arr[i], static_cast<int64_t>(0));
        tree[TREESIZE + i].end = std::max(arr[i], static_cast<int64_t>(0));
        tree[TREESIZE + i].best = std::max(arr[i], static_cast<int64_t>(0));
    }

    for (std::size_t i = TREESIZE - 1; i > 0; --i) {
        tree[i].sum = tree[2 * i].sum + tree[2 * i + 1].sum;
        tree[i].start = std::max(tree[2 * i].start, tree[2 * i].sum + tree[2 * i + 1].start);
        tree[i].end = std::max(tree[2 * i + 1].end, tree[2 * i + 1].sum + tree[2 * i].end);
        tree[i].best = std::max(std::max(tree[2 * i].best, tree[2 * i + 1].best), tree[2 * i].end + tree[2 * i + 1].start);
    }
}

void update(std::size_t id, int64_t x) {
    tree[id].sum = x;
    tree[id].start = std::max(x, static_cast<int64_t>(0));
    tree[id].end = std::max(x, static_cast<int64_t>(0));
    tree[id].best = std::max(x, static_cast<int64_t>(0));

    id /= 2;

    while (id > 0) {
        tree[id].sum = tree[2 * id].sum + tree[2 * id + 1].sum;
        tree[id].start = std::max(tree[2 * id].start, tree[2 * id].sum + tree[2 * id + 1].start);
        tree[id].end = std::max(tree[2 * id + 1].end, tree[2 * id + 1].sum + tree[2 * id].end);
        tree[id].best = std::max(std::max(tree[2 * id].best, tree[2 * id + 1].best), tree[2 * id].end + tree[2 * id + 1].start);

        id /= 2;
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::vector<int64_t> arr;
    std::size_t n, m, k, x;

    std::cin >> n >> m;

    arr.resize(n);
    for (auto& x : arr) {
        std::cin >> x;
    }

    tree_init(arr);

    while (m--) {
        std::cin >> k >> x;
        update(TREESIZE + k - 1, x);
        std::cout << tree[1].best << "\n";
    }

    return 0;
}