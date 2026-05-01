#include <iostream>
#include <vector>
#include <array>
#include <cstdint>
#include <numeric>

constexpr int64_t INF = 1e14;
constexpr std::size_t MAXN = 2e5 + 5;

constexpr std::size_t calculate_tree_size(std::size_t maxn) {
    std::size_t res = 1;

    while (res < maxn) {
        res <<= 1;
    }

    return res;
}

constexpr std::size_t TREESIZE = calculate_tree_size(MAXN);

std::array<int64_t, 2 * TREESIZE> tree;
std::array<int64_t, 2 * TREESIZE> residual;

void tree_init(std::vector<int64_t> const& arr) {
    std::fill(tree.begin(), tree.end(), -INF);

    for (std::size_t i = 0; i < arr.size(); ++i) {
        tree[TREESIZE + i] = arr[i];
    }

    for (std::size_t i = TREESIZE - 1; i > 0; --i) {
        tree[i] = std::max(tree[2 * i], tree[2 * i + 1]);
    }
}

void push_down(std::size_t id) {
    tree[id] += residual[id];
    
    if (id < TREESIZE) {
        residual[2 * id] += residual[id];
        residual[2 * id + 1] += residual[id];
    }

    residual[id] = 0;
}

void update(std::size_t id, std::size_t low, std::size_t top, std::size_t i, std::size_t j, int64_t x) {
    push_down(id);

    if (top < i || low > j) {
        return;
    } else if (low >= i && top <= j) {
        residual[id] += x;
        push_down(id);
        return;
    }

    std::size_t mid = (top + low) / 2;
    update(2 * id, low, mid, i, j, x);
    update(2 * id + 1, mid + 1, top, i, j, x);

    tree[id] = std::max(tree[2 * id], tree[2 * id + 1]);
}

int64_t query(std::size_t id, std::size_t low, std::size_t top, std::size_t i, std::size_t j) {
    push_down(id);

    if (top < i || low > j) {
        return -INF;
    } else if (low >= i && top <= j) {
        return tree[id];
    }

    std::size_t mid = (top + low) / 2;
    auto left = query(2 * id, low, mid, i, j);
    auto right = query(2 * id + 1, mid + 1, top, i, j);

    return std::max(left, right);
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::vector<int64_t> arr;
    std::vector<int64_t> pref;
    std::size_t n, q;
    int64_t a, b;
    char c;

    std::cin >> n >> q;

    arr.resize(n);
    pref.resize(n);

    for (auto& x : arr) {
        std::cin >> x;
    }

    std::partial_sum(arr.begin(), arr.end(), pref.begin());
    tree_init(pref);

    while (q--) {
        std::cin >> c >> a >> b;

        if (c == '1') {
            auto diff = b - arr[a - 1];
            update(1, TREESIZE, 2 * TREESIZE - 1, a + TREESIZE - 1, n + TREESIZE - 1, diff);
            arr[a - 1] = b;
        } else {
            int64_t curr = query(1, TREESIZE, 2 * TREESIZE - 1, a + TREESIZE - 1, b + TREESIZE - 1);
        
            int64_t prev = 0;
            if (a > 1) {
                prev = query(1, TREESIZE, 2 * TREESIZE - 1, a + TREESIZE - 2, a + TREESIZE - 2);
            }
            
            std::cout << std::max(curr - prev, static_cast<int64_t>(0ll)) << "\n";
        }
    }

    return 0;
}