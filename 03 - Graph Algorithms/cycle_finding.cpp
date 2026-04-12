#include <iostream>
#include <vector>
#include <cstdint>

constexpr int64_t INF = 1e14 + 14;

struct edge {
    std::size_t a;
    std::size_t b;
    int64_t c;
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::vector<edge> edges;
    std::vector<int64_t> dist;
    std::vector<std::size_t> prev;
    std::vector<std::size_t> cycle;
    std::size_t n, m, a, b, x;
    int64_t c;

    std::cin >> n >> m;

    dist.resize(n + 1, 0);
    prev.resize(n + 1, 0);

    while (m--) {
        std::cin >> a >> b >> c;
        edges.push_back({a, b, c});
    }

    for (std::size_t i = 0; i < n; ++i) {
        x = 0;

        for (auto const& e : edges) {
            if (dist[e.a] + e.c < dist[e.b]) {
                dist[e.b] = dist[e.a] + e.c;
                prev[e.b] = e.a;
                x = e.b;
            }
        }
    }

    if (x) {
        for (std::size_t i = 0; i < n; ++i) {
            x = prev[x];
        }

        for (std::size_t v = x;; v = prev[v]) {
            cycle.push_back(v);

            if (v == x && cycle.size() > 1) {
                break;
            }
        }

        std::cout << "YES\n";
        for (auto it = cycle.rbegin(); it != cycle.rend(); ++it) {
            std::cout << *it << " ";
        }
    } else {
        std::cout << "NO";
    }

    std::cout << "\n";
    return 0;
}