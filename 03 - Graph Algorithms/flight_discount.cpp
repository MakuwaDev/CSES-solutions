#include <iostream>
#include <vector>
#include <queue>
#include <limits>

constexpr std::size_t INF = std::numeric_limits<std::size_t>::max();

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::vector<std::vector<std::pair<std::size_t, std::size_t>>> graph;
    std::vector<std::size_t> dist;
    std::priority_queue<std::pair<std::size_t, std::size_t>,
                        std::vector<std::pair<std::size_t, std::size_t>>,
                        std::greater<std::pair<std::size_t, std::size_t>>> q;

    std::size_t n, m, a, b, c;
    std::cin >> n >> m;

    graph.resize(2 * n);
    dist.resize(2 * n, INF);

    while (m--) {
        std::cin >> a >> b >> c;
        --a; --b;

        graph[a].push_back({b, c});
        graph[a].push_back({b + n, c / 2});
        graph[a + n].push_back({b + n, c});
    }

    q.push({0, 0});

    while (!q.empty()) {
        auto [d, v] = q.top();
        q.pop();

        if (dist[v] != INF) {
            continue;
        }

        dist[v] = d;

        for (auto const& [u, l] : graph[v]) {
            q.push({d + l, u});
        }
    }

    std::cout << dist.back() << "\n";
    return 0;
}