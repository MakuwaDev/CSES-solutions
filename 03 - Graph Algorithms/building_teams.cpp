#include <iostream>
#include <vector>
#include <cstdint>

std::vector<std::vector<std::size_t>> graph;
std::vector<int8_t> team;

bool dfs(std::size_t v, int8_t side) {
    bool success = true;

    team[v] = side;

    for (auto const& u : graph[v]) {
        if (team[u] == side) {
            return false;
        } else if (team[u] == 0) {
            success &= dfs(u, side * -1);
        }
    }

    return success;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    bool success = true;

    std::size_t n, m, a, b;
    std::cin >> n >> m;

    graph.resize(n + 1);
    team.resize(n + 1);
    for (std::size_t i = 0; i < m; ++i) {
        std::cin >> a >> b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    for (std::size_t i = 1; i <= n; ++i) {
        if (team[i] == 0) {
            success &= dfs(i, 1);
        }
    }

    if (success) {
        for (std::size_t i = 1; i <= n; ++i) {
            std::cout << (team[i] == 1 ? 1 : 2) << " ";
        }
    } else {
        std::cout << "IMPOSSIBLE\n";
    }

    return 0;
}