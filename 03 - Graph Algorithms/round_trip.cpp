#include <iostream>
#include <vector>

std::vector<std::vector<std::size_t>> graph;
std::vector<bool> visited;
std::vector<std::size_t> prev;

std::pair<std::size_t, std::size_t> dfs(std::size_t curr, std::size_t parent) {
    visited[curr] = true;
    prev[curr] = parent;

    for (auto const& next : graph[curr]) {
        if (!visited[next]) {
            auto [a, b] = dfs(next, curr);

            if (a != b) {
                return {a, b};
            }
        } else if (next != parent) {
            return {curr, next};
        }
    }

    return {curr, curr};
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::vector<std::size_t> cycle;

    std::size_t n, m, a, b;
    std::cin >> n >> m;

    graph.resize(n);
    visited.resize(n);
    prev.resize(n);

    for (std::size_t i = 0; i < m; ++i) {
        std::cin >> a >> b;
        --a; --b;

        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    for (std::size_t i = 0; i < n; ++i) {
        if (!visited[i]) {
            auto [a, b] = dfs(i, i);

            if (a != b) {
                cycle.push_back(b);

                for (; a != b; a = prev[a]) {
                    cycle.push_back(a);
                }

                cycle.push_back(b);

                std::cout << cycle.size() << "\n";

                for (auto const& v : cycle) {
                    std::cout << v + 1 << " ";
                }

                std::cout << "\n";
                return 0;
            }
        }
    }

    std::cout << "IMPOSSIBLE\n";
    return 0;
}