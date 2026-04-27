#include <iostream>
#include <cstdint>
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

std::array<int64_t, 2 * TREESIZE> tree;

std::vector<std::vector<std::size_t>> graph;
std::vector<int64_t> val;
std::vector<std::size_t> pre;
std::vector<std::size_t> maxpre;
std::vector<int64_t> depth;

std::size_t t = 0;

void dfs(std::size_t v, std::size_t p) {
    maxpre[v] = pre[v] = t++;
    depth[v] = depth[p] + val[v];

    for (auto const& u : graph[v]) {
        if (u != p) {
            dfs(u, v);
            maxpre[v] = std::max(maxpre[v], maxpre[u]);
        }
    }
}

void update(std::size_t id, std::size_t low, std::size_t top, std::size_t i, std::size_t j, int64_t x) {
    if (top < i || low > j) {
        return;
    } else if (low >= i && top <= j) {
        tree[id] += x;
        return;
    }

    std::size_t mid = (top + low) / 2;
    update(2 * id, low, mid, i, j, x);
    update(2 * id + 1, mid + 1, top, i, j, x);
}

int64_t query(std::size_t id) {
    int64_t x = 0;

    while (id > 0) {
        x += tree[id];
        id /= 2;
    }

    return x;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    char c;
    std::size_t n, q, a, b, s, x;

    std::cin >> n >> q;

    graph.resize(n);
    val.resize(n);
    pre.resize(n);
    maxpre.resize(n);
    depth.resize(n);

    for (auto& v : val) {
        std::cin >> v;
    }

    for (std::size_t e = 0; e < n - 1; ++e) {
        std::cin >> a >> b;
        --a;
        --b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    dfs(0, 0);

    for (std::size_t v = 0; v < n; ++v) {
        tree[TREESIZE + pre[v]] = depth[v];
    }

    while (q--) {
        std::cin >> c >> s;
        --s;

        if (c == '1') {
            std::cin >> x;
            update(1, TREESIZE, 2 * TREESIZE - 1, TREESIZE + pre[s], TREESIZE + maxpre[s], x - val[s]);
            val[s] = x;
        } else {
            std::cout << query(TREESIZE + pre[s]) << "\n";
        }
    }

    return 0;
}