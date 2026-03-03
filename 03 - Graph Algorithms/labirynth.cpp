#include <iostream>
#include <array>
#include <vector>
#include <queue>
#include <cstdint>

constexpr std::size_t MOVE_COUNT = 4;
constexpr std::array<int32_t, MOVE_COUNT> dx = {1, -1, 0, 0};
constexpr std::array<int32_t, MOVE_COUNT> dy = {0, 0, 1, -1};
constexpr std::array<char, MOVE_COUNT> move = {'D', 'U', 'R', 'L'};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::vector<std::string> grid;
    std::vector<std::vector<int32_t>> dist;
    std::vector<std::vector<int8_t>> prev;
    std::queue<std::pair<int32_t, int32_t>> q;
    std::string path = "";

    int32_t n, m, ax, ay, bx, by, x, y;
    std::cin >> n >> m;

    grid.resize(n);
    dist.resize(n);
    prev.resize(n);

    for (int32_t i = 0; i < n; ++i) {
        std::cin >> grid[i];
        dist[i].resize(m);
        prev[i].resize(m);

        std::fill(dist[i].begin(), dist[i].end(), -1);
        std::fill(prev[i].begin(), prev[i].end(), -1);

        for (int32_t j = 0; j < m; ++j) {
            if (grid[i][j] == 'A') {
                ax = i;
                ay = j;
            } else if (grid[i][j] == 'B') {
                bx = i;
                by = j;
            }
        }
    }

    q.push({ax, ay});
    dist[ax][ay] = 0;
    prev[ax][ay] = 69;
    while (!q.empty()) {
        auto &[x, y] = q.front();
        q.pop();

        for (std::size_t i = 0; i < MOVE_COUNT; ++i) {
            auto nx = x + dx[i];
            auto ny = y + dy[i];

            if (nx < 0 || nx >= n || ny < 0 || ny >= m) {
                continue;
            }

            if (grid[nx][ny] == '#' || dist[nx][ny] != -1) {
                continue;
            }

            dist[nx][ny] = dist[x][y] + 1;
            prev[nx][ny] = i;
            q.push({nx, ny});
        }
    }

    if (dist[bx][by] != -1) {
        std::cout << "YES\n" << dist[bx][by] << "\n";

        x = bx;
        y = by;
        while (prev[x][y] != 69) {
            path.push_back(move[prev[x][y]]);
            auto tx = x;
            
            x -= dx[prev[tx][y]];
            y -= dy[prev[tx][y]];
        }

        for (auto c = path.rbegin(); c != path.rend(); ++c) {
            std::cout << *c;
        }

        std::cout << "\n";
    } else {
        std::cout << "NO\n";
    }

    return 0;
}