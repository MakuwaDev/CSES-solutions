#include <iostream>
#include <vector>

constexpr std::size_t INF = 5e5;

std::vector<std::vector<std::size_t>> graph;
std::vector<std::size_t> dist;

void dfs(std::size_t v, std::size_t d) {
    dist[v] = d;

    for (auto const& u : graph[v]) {
        if (dist[u] == INF) {
            dfs(u, d + 1);
        }
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::size_t n, a, b, s = 0;

    std::cin >> n;

    graph.resize(n);
    dist.resize(n, INF);

    for (std::size_t i = 1; i < n; ++i) {
        std::cin >> a >> b;
        --a; --b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    dfs(0, 0);

    for (std::size_t i = 0; i < n; ++i) {
        if (dist[i] > dist[s]) {
            s = i;
        }
    }

    std::fill(dist.begin(), dist.end(), INF);
    dfs(s, 0);

    for (std::size_t i = 0; i < n; ++i) {
        if (dist[i] > dist[s]) {
            s = i;
        }
    }

    std::cout << dist[s] << "\n";
    return 0;
}