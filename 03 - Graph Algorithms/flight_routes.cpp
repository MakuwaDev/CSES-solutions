#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

constexpr std::size_t INF = 1e16 + 16;

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::vector<std::vector<std::pair<std::size_t, std::size_t>>> graph;
    std::vector<std::vector<std::size_t>> dist;
    std::priority_queue<std::pair<std::size_t, std::size_t>,
                        std::vector<std::pair<std::size_t, std::size_t>>,
                        std::greater<std::pair<std::size_t, std::size_t>>> q;

    std::size_t n, m, k, a, b, c;
    std::cin >> n >> m >> k;

    graph.resize(n);
    dist.resize(n);
    for (auto& v : dist) {
        v.resize(k, INF);
    }

    while (m--) {
        std::cin >> a >> b >> c;
        --a; --b;
        graph[a].push_back({c, b});
    }

    dist[0][0] = 0;
    q.push({0, 0});

    while (!q.empty()) {
        auto [d, v] = q.top();
        q.pop();

        if (d > dist[v].back()) {
            continue;
        }

        for (auto const& [c, u] : graph[v]) {
            if (d + c < dist[u].back()) {
                auto it = std::upper_bound(dist[u].begin(), dist[u].end(), d + c);

                dist[u].insert(it, d + c);
                dist[u].pop_back();

                q.push({d + c, u});
            }
        }
    }

    for (auto const& d : dist[n - 1]) {
        std::cout << d << " ";
    }

    std::cout << "\n";
    return 0;
}