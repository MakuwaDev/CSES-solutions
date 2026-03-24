#include <iostream>
#include <vector>
#include <queue>
#include <array>
#include <cstdint>

constexpr std::size_t MOVE_COUNT = 4;
constexpr std::array<int32_t, MOVE_COUNT> dx = {1, -1, 0, 0};
constexpr std::array<int32_t, MOVE_COUNT> dy = {0, 0, 1, -1};
constexpr std::array<char, MOVE_COUNT> move = {'D', 'U', 'R', 'L'};

struct visitor {
    int32_t x;
    int32_t y;
    int8_t type;
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    std::vector<std::string> grid;
    std::vector<std::vector<int8_t>> visited;
    std::vector<std::vector<int8_t>> prev;
    std::queue<visitor> q;
    std::vector<std::pair<int32_t, int32_t>> monsters;
    std::string path = "";
    int32_t n, m, ax, ay, x, y, lx, ly;
    bool found = false;

    std::cin >> n >> m;

    grid.resize(n);
    visited.resize(n);
    prev.resize(n);

    for (int32_t i = 0; i < n; ++i) {
        std::cin >> grid[i];
        visited[i].resize(m, -1);
        prev[i].resize(m, -1);

        for (int32_t j = 0; j < m; ++j) {
            if (grid[i][j] == 'A') {
                ax = i;
                ay = j;
            } else if (grid[i][j] == 'M') {
                monsters.push_back({i, j});
            }
        }
    }

    for (auto const& mon : monsters) {
        q.push({mon.first, mon.second, 1});
        visited[mon.first][mon.second] = 1;
    }

    q.push({ax, ay, 0});
    visited[ax][ay] = 0;
    prev[ax][ay] = 69;

    while (!q.empty()) {
        auto [x, y, t] = q.front();
        q.pop();

        if (t == 0 && (x == 0 || x == n - 1 || y == 0 || y == m - 1)) {
            found = true;
            lx = x;
            ly =  y;
            break;
        }

        for (std::size_t i = 0; i < MOVE_COUNT; ++i) {
            auto nx = x + dx[i];
            auto ny = y + dy[i];

            if (nx < 0 || nx >= n || ny < 0 || ny >= m) {
                continue;
            }

            if (grid[nx][ny] == '#' || visited[nx][ny] != -1) {
                continue;
            }

            visited[nx][ny] = t;
            prev[nx][ny] = i;
            q.push({nx, ny, t});
        }
    }

    if (found) {
        std::cout << "YES\n";

        x = lx;
        y = ly;

        while (prev[x][y] != 69) {
            path.push_back(move[prev[x][y]]);
            auto tx = x;

            x -= dx[prev[tx][y]];
            y -= dy[prev[tx][y]];
        }

        std::cout << path.size() << "\n";
        for (auto it = path.rbegin(); it != path.rend(); ++it) {
            std::cout << *it;
        }

        std::cout << "\n";
    } else {
        std::cout << "NO\n";
    }

    return 0;
}