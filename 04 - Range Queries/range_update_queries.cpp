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
}

void update_impl(std::size_t id, std::size_t x, std::size_t l, std::size_t r, std::size_t i, std::size_t j) {
    if (r < i || l > j) {
        return;
    } else if (l >= i && r <= j) {
        tree[id] += x;
        return;
    }

    std::size_t mid = (r + l) / 2;
    update_impl(2 * id, x, l, mid, i, j);
    update_impl(2 * id + 1, x, mid + 1, r, i, j);
}

void update(std::size_t i, std::size_t j, std::size_t x) {
    update_impl(1, x, TREESIZE, 2 * TREESIZE - 1, i + TREESIZE - 1, j + TREESIZE - 1);
}

std::size_t query_impl(std::size_t id) {
    std::size_t res = 0;

    while (id > 0) {
        res += tree[id];
        id /= 2;
    }

    return res;
}

std::size_t query(std::size_t id) {
    return query_impl(id + TREESIZE - 1);
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    std::vector<std::size_t> arr;
    std::size_t n, q, a, b, u, k, type;

    std::cin >> n >> q;

    arr.resize(n);
    for (auto& x : arr) {
        std::cin >> x;
    }

    tree_init(arr);

    while (q--) {
        std::cin >> type;

        switch (type) {
            case 1:
                std::cin >> a >> b >> u;
                update(a, b, u);
                break;
            case 2:
                std::cin >> k;
                std::cout << query(k) << "\n";
                break;
            default:
                return 1;
        }
    }

    return 0;
}