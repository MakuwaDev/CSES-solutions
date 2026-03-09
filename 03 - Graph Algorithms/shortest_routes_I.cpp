#include <iostream>
#include <cstdint>
#include <vector>
#include <limits>
#include <queue>

constexpr uint64_t INF = std::numeric_limits<uint64_t>::max();

using queue_element = std::pair<uint64_t, uint32_t>;
using pqueue = std::priority_queue<queue_element, std::vector<queue_element>, std::greater<queue_element>>;

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::vector<std::vector<std::pair<uint32_t, uint64_t>>> graph;
    std::vector<uint64_t> dist;
    pqueue q;

    uint32_t n, m, a, b;
    uint64_t d;
    std::cin >> n >> m;

    graph.resize(n);
    dist.resize(n);
    std::fill(dist.begin(), dist.end(), INF);

    for (uint32_t i = 0; i < m; ++i) {
        std::cin >> a >> b >> d;
        --a; --b;
        graph[a].push_back({b, d});
    }

    dist[0] = 0;
    q.push({0, 0});

    while (!q.empty()) {
        auto [d, v] = q.top();
        q.pop();

        if (d > dist[v]) {
            continue;
        }

        for (auto const& [u, edge] : graph[v]) {
            if (dist[u] > d + edge) {
                dist[u] = d + edge;
                q.push({dist[u], u});
            }
        }
    }

    for (auto const& d : dist) {
        std::cout << d << " ";
    }

    std::cout << "\n";
    return 0;
}