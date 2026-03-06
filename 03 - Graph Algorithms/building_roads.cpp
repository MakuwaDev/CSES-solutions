#include <iostream>
#include <vector>

void dfs(std::vector<std::vector<std::size_t>> const& graph, std::vector<bool>& visited, std::size_t u) {
    visited[u] = true;
    for (auto const& v : graph[u]) {
        if (!visited[v]) {
            dfs(graph, visited, v);
        }
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::vector<std::vector<std::size_t>> graph;
    std::vector<bool> visited;
    std::vector<std::size_t> reps;

    std::size_t n, m, a, b;
    std::cin >> n >> m;

    graph.resize(n + 1);
    visited.resize(n + 1);

    for (std::size_t i = 0; i < m; ++i) {
        std::cin >> a >> b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    for (std::size_t i = 1; i <= n; ++i) {
        if (!visited[i]) {
            reps.push_back(i);
            dfs(graph, visited, i);
        }
    }

    std::cout << reps.size() - 1 << "\n";

    for (std::size_t i = 1; i < reps.size(); ++i) {
        std::cout << reps[i - 1] << " " << reps[i] << "\n";
    }

    return 0;
}