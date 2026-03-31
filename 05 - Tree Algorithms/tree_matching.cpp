#include <iostream>
#include <vector>

std::vector<std::vector<std::size_t>> graph;
std::vector<std::size_t> dp1, dp2;

void dfs(std::size_t v, std::size_t parent) {
    dp1[v] = 0;
    dp2[v] = 0;

    for (auto const& u : graph[v]) {
        if (u != parent) {
            dfs(u, v);
            dp1[v] += std::max(dp1[u], dp2[u]);
        }
    }

    for (auto const& u : graph[v]) {
        if (u != parent) {
            dp2[v] = std::max(dp2[v], dp1[v] - std::max(dp1[u], dp2[u]) + dp1[u] + 1);
        }
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::size_t n, a, b;

    std::cin >> n;

    graph.resize(n);
    dp1.resize(n);
    dp2.resize(n);

    for (std::size_t i = 1; i < n; ++i) {
        std::cin >> a >> b;
        --a; --b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }
    
    dfs(0, 0);

    std::cout << std::max(dp1[0], dp2[0]) << "\n";
    return 0;
}