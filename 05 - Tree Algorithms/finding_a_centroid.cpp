#include <iostream>
#include <vector>

std::size_t n;
std::vector<std::vector<std::size_t>> graph;
std::vector<std::size_t> subtree;

std::size_t dfs1(std::size_t v, std::size_t p) {
    for (auto const& u : graph[v]) {
        if (u != p) {
            subtree[v] += dfs1(u, v);
        }
    }

    return ++subtree[v];
}

std::size_t dfs2(std::size_t v, std::size_t p) {
    for (auto const& u : graph[v]) {
        if (u != p && subtree[u] > n / 2) {
            return dfs2(u, v);
        }
    }

    return v;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::size_t a, b;

    std::cin >> n;

    graph.resize(n + 1);
    subtree.resize(n + 1);

    for (std::size_t i = 1; i < n; ++i) {
        std::cin >> a >> b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    dfs1(1, 1);
    std::cout << dfs2(1, 1) << "\n";
    return 0;
}