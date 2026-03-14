#include <iostream>
#include <vector>
#include <array>

constexpr std::size_t MAXN = 2e5 + 5;

constexpr std::size_t calculate_tree_size(std::size_t MAXN) {
    std::size_t res = 1;

    while (res < MAXN) {
        res <<= 1;
    }

    return res;
}

constexpr std::size_t TREESIZE = 2 * calculate_tree_size(MAXN);

std::array<std::size_t, 2 * TREESIZE> tree;

void tree_init(std::vector<std::size_t> const& arr) {
    for (std::size_t i = 0; i < arr.size(); ++i) {
        tree[TREESIZE + i] = arr[i];
    }

    for (std::size_t i = TREESIZE - 1; i > 0; --i) {
        tree[i] = tree[2 * i] + tree[2 * i + 1];
    }
}

void update_impl(std::size_t id, std::size_t x) {
    tree[id] = x;
    id /= 2;

    while (id > 0) {
        tree[id] = tree[2 * id] + tree[2 * id + 1];
        id /= 2;
    }
}

void update(std::size_t id, std::size_t x) {
    update_impl(id + TREESIZE - 1, x);
}

std::size_t query_impl(std::size_t id, std::size_t low, std::size_t top, std::size_t i, std::size_t j) {
    if (top < i || low > j) {
        return 0;
    } else if (low >= i && top <= j) {
        return tree[id];
    }

    std::size_t mid = (top + low) / 2;
    return query_impl(2 * id, low, mid, i, j) + query_impl(2 * id + 1, mid + 1, top, i, j);
}

std::size_t query(std::size_t i, std::size_t j) {
    return query_impl(1, TREESIZE, 2 * TREESIZE - 1, i + TREESIZE - 1, j + TREESIZE - 1);
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::vector<std::size_t> arr;
    std::size_t n, q, a, b, type;

    std::cin >> n >> q;

    arr.resize(n);
    for (auto& x : arr) {
        std::cin >> x;
    }

    tree_init(arr);

    while (q--) {
        std::cin >> type >> a >> b;

        switch (type) {
            case 1:
                update(a, b);
                break;
            case 2:
                std::cout << query(a, b) << "\n";
                break;
            default:
                return 1;
        }
    }

    return 0;
}