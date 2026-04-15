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

void tree_init(std::vector<std::size_t> const& arr) {
    for (std::size_t i = 0; i < arr.size(); ++i) {
        tree[TREESIZE + i] = arr[i];
    }

    for (std::size_t i = TREESIZE - 1; i > 0; --i) {
        tree[i] = std::max(tree[2 * i], tree[2 * i + 1]);
    }
}

void update(std::size_t id, std::size_t x) {
    tree[id] -= x;
    id /= 2;

    while (id > 0) {
        tree[id] = std::max(tree[2 * id], tree[2 * id + 1]);
        id /= 2;
    }
}

std::size_t query(std::size_t id, std::size_t x) {
    if (id >= TREESIZE) {
        return tree[id] >= x ? id : 2 * TREESIZE;
    }

    if (tree[2 * id] >= x) {
        return query(2 * id, x);
    } else if (tree[2 * id + 1] >= x) {
        return query(2 * id + 1, x);
    } else {
        return 2 * TREESIZE;
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::vector<std::size_t> rooms;
    std::size_t n, m, g, h;

    std::cin >> n >> m;

    rooms.resize(n);
    for (auto& r : rooms) {
        std::cin >> r;
    }

    tree_init(rooms);

    while (m--) {
        std::cin >> g;

        h = query(1, g);
        if (h != 2 * TREESIZE) {
            update(h, g);
            std::cout << h - TREESIZE + 1 << " ";
        } else {
            std::cout << "0 ";
        }
    }

    std::cout << "\n";
    return 0;
}