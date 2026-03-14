#include <iostream>
#include <vector>
#include <cstdint>
#include <numeric>

constexpr uint64_t INF = std::numeric_limits<uint64_t>::max();

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::vector<std::vector<uint64_t>> dist;
    std::size_t n, m, q, a, b;
    uint64_t c;

    std::cin >> n >> m >> q;

    dist.resize(n);
    for (std::size_t i = 0; i < n; ++i) {
        dist[i].resize(n, INF);
        dist[i][i] = 0;
    }

    while (m--) {
        std::cin >> a >> b >> c;
        --a; --b;

        dist[a][b] = std::min(dist[a][b], c);
        dist[b][a] = dist[a][b];
    }

    for (std::size_t x = 0; x < n; ++x) {
        for (std::size_t u = 0; u < n; ++u) {
            for (std::size_t v = 0; v < n; ++v) {
                if (dist[u][x] != INF && dist[x][v] != INF) {
                    dist[u][v] = std::min(dist[u][v], dist[u][x] + dist[x][v]);
                }
            }
        }
    }

    while (q--) {
        std::cin >> a >> b;
        --a; --b;

        int64_t d = dist[a][b] != INF ? dist[a][b] : -1; 
        std::cout << d << "\n";
    }

    return 0;
}