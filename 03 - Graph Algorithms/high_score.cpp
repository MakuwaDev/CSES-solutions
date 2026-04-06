#include <iostream>
#include <vector>
#include <cstdint>

constexpr int64_t INF = 1e14 + 14;

struct edge {
    std::size_t u;
    std::size_t v;
    int64_t w;
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::vector<int64_t> dist;
    std::vector<edge> edges;
    std::size_t n, m, a, b;
    int64_t c;

    std::cin >> n >> m;

    dist.resize(n, INF);
    dist[0] = 0;

    while (m--) {
        std::cin >> a >> b >> c;
        --a; --b;
        edges.push_back({a, b, -c});
    }

    for (std::size_t i = 0; i < n - 1; ++i) {
        for (auto const& e : edges) {
            if (dist[e.u] != INF && dist[e.v] > dist[e.u] + e.w) {
                dist[e.v] = std::max<int64_t>(-INF, dist[e.u] + e.w);
            }
        }
    }

    for (std::size_t i = 0; i < n; ++i) {
        for (auto const& e : edges) {
            if (dist[e.u] != INF && dist[e.v] > dist[e.u] + e.w) {
                dist[e.v] = -INF;
            }
        }
    }

    if (dist[n - 1] == -INF) {
        std::cout << "-1\n";
    } else {
        std::cout << -dist[n - 1] << "\n";
    }

    return 0;
}