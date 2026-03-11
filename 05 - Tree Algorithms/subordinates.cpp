#include <iostream>
#include <vector>

std::vector<std::vector<std::size_t>> graph;
std::vector<std::size_t> subs;

std::size_t dfs(std::size_t v) {
    for (auto const& u : graph[v]) {
        subs[v] += dfs(u) + 1;
    }

    return subs[v];
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::size_t n, x;
    std::cin >> n;

    graph.resize(n);
    subs.resize(n);

    for (std::size_t i = 1; i < n; ++i) {
        std::cin >> x;
        graph[x - 1].push_back(i);
    }

    dfs(0);

    for (auto const& x : subs) {
        std::cout << x << " ";
    }

    std::cout << "\n";
    return 0;
}