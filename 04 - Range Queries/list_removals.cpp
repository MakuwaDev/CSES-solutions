#include <iostream>
#include <vector>
#include <array>

constexpr std::size_t MAXN = 2e5 + 5;

constexpr std::size_t calculate_tree_size(std::size_t maxn) {
    std::size_t res = 1;

    while (res < maxn) {
        res <<= 1;
    }

    return res;
}

constexpr std::size_t TREESIZE = calculate_tree_size(MAXN);

std::array<std::size_t, 2 * TREESIZE> tree;

void tree_init(std::size_t n) {
    for (std::size_t i = 0; i <n; ++i) {
        tree[TREESIZE + i] = 1;
    }

    for (std::size_t i = TREESIZE - 1; i > 0; --i) {
        tree[i] = tree[2 * i] + tree[2 * i + 1];
    }
}

void update(std::size_t id) {
    tree[id] = 0;
    id /= 2;

    while (id > 0) {
        tree[id] = tree[2 * id] + tree[2 * id + 1];
        id /= 2;
    }
}

std::size_t query(std::size_t id, std::size_t x) {
    if (id >= TREESIZE) {
        return id;
    }

    if (tree[2 * id] >= x) {
        return query(2 * id, x);
    } else {
        return query(2 * id + 1, x - tree[2 * id]);
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::vector<std::size_t> arr;
    std::size_t n, p, np;

    std::cin >> n;

    arr.resize(n);
    for (auto& a : arr) {
        std::cin >> a;
    }

    tree_init(n);

    for (std::size_t _ = 0; _ < n; ++_) {
        std::cin >> p;
        
        np = query(1, p);
        update(np);

        std::cout << arr[np - TREESIZE] << " ";
    }

    std::cout << "\n";
    return 0;
}