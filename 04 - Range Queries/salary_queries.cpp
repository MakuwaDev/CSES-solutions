#include <iostream>
#include <vector>
#include <array>
#include <algorithm>

constexpr std::size_t MAXN = 6e5 + 4;

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

void update_impl(std::size_t id1, std::size_t id2) {
    --tree[id1];
    ++tree[id2];
    
    id1 /= 2;
    id2 /= 2;

    while (id1 > 0) {
        tree[id1] = tree[2 * id1] + tree[2 * id1 + 1];
        
        if (id1 != id2) {
            tree[id2] = tree[2 * id2] + tree[2 * id2 + 1];
        }
        
        id1 /= 2;
        id2 /= 2;
    }
}

void update(std::size_t id1, std::size_t id2) {
    update_impl(id1 + TREESIZE - 1, id2 + TREESIZE - 1);
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

struct task {
    char c;
    std::size_t a;
    std::size_t b;
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::vector<std::size_t> scale;
    std::vector<std::size_t> salaries;
    std::vector<task> queries;
    std::size_t n, q;

    std::cin >> n >> q;

    salaries.resize(n);
    queries.resize(q);
    scale.reserve(n + 2 * q);

    for (auto& x : salaries) {
        std::cin >> x;
        scale.push_back(x);
    }

    for (std::size_t i = 0; i < q; ++i) {
        std::cin >> queries[i].c >> queries[i].a >> queries[i].b;
        
        scale.push_back(queries[i].b);
        if (queries[i].c == '?') {
            scale.push_back(queries[i].a);
        }
    }

    std::sort(scale.begin(), scale.end());
    scale.erase(std::unique(scale.begin(), scale.end()), scale.end());

    auto get_scale = [&](std::size_t x) {
        return std::lower_bound(scale.begin(), scale.end(), x) - scale.begin() + 1;
    };

    tree_init([&]() {
        std::vector<std::size_t> tmp;
        tmp.resize(scale.size());

        for (auto const& x : salaries) {
            ++tmp[get_scale(x) - 1];
        }

        return tmp;
    }());

    for (auto const& t : queries) {
        if (t.c == '!') {
            auto prev = salaries[t.a - 1];
            update(get_scale(prev), get_scale(t.b));
            salaries[t.a - 1] = t.b;
        } else {
            std::cout << query(get_scale(t.a), get_scale(t.b)) << "\n";
        }
    }

    return 0;
}