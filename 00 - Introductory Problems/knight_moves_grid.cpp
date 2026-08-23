#include <iostream>
#include <vector>
#include <queue>
#include <cstdint>

constexpr int32_t INF = 1e9 + 7;

constexpr int32_t move[8][2] = {{1, 2}, {1, -2}, {-1, 2}, {-1, -2}, {2, 1}, {2, -1}, {-2, 1}, {-2, -1}};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int32_t n, nr, nc;
    std::vector<std::vector<int32_t>> dist;
    std::queue<std::pair<int32_t, int32_t>> q;

    std::cin >> n;

    dist.resize(n);
    for (auto& x : dist) {
        x.resize(n, INF);
    }

    q.push({0, 0});
    dist[0][0] = 0;

    while (!q.empty()) {
        auto [r, c] = q.front();
        q.pop();

        for (auto& [dr, dc] : move) {
            nr = r + dr;
            nc = c + dc;

            if (nr >= 0 && nr < n && nc >= 0 && nc < n && dist[nr][nc] == INF) {
                dist[nr][nc] = dist[r][c] + 1;
                q.push({nr, nc});
            } 
        }
    }

    for (auto& r : dist) {
        for (auto& c : r) {
            std::cout << c << " ";
        }

        std::cout << "\n";
    }
}