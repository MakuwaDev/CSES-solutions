#include <iostream>
#include <vector>

std::vector<std::vector<std::size_t>> graph;

void dfs(std::size_t v, std::size_t parent, std::vector<std::size_t>& dist) {
    dist[v] = dist[parent] + 1;

    for (auto const& u : graph[v]) {
        if (u != parent) {
            dfs(u, v, dist);
        }
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::vector<std::size_t> dist;
    std::vector<std::size_t> distA;
    std::vector<std::size_t> distB;
    std::size_t n, a, b;

    std::cin >> n;
    graph.resize(n);
    dist.resize(n);
    distA.resize(n);
    distB.resize(n);

    for (std::size_t i = 1; i < n; ++i) {
        std::cin >> a >> b;
        --a; --b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    dist[0] = -1;
    dfs(0, 0, dist);

    a = 0;
    for (std::size_t i = 0; i < n; ++i) {
        if (dist[a] < dist[i]) {
            a = i;
        }
    }

    distA[a] = -1;
    dfs(a, a, distA);

    b = a;
    for (std::size_t i = 0; i < n; ++i) {
        if (distA[b] < distA[i]) {
            b = i;
        }
    }

    distB[b] = -1;
    dfs(b, b, distB);

    for (std::size_t i = 0; i < n; ++i) {
        std::cout << std::max(distA[i], distB[i]) << " ";
    }

    std::cout << "\n";
    return 0;
}