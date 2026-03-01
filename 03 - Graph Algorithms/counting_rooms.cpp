#include <iostream>
#include <cstdint>
#include <vector>
#include <queue>

constexpr int8_t dx[4] = {-1, 1, 0, 0};
constexpr int8_t dy[4] = {0, 0, -1, 1};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::vector<std::vector<bool>> visited;
    std::vector<std::string> map;
    std::queue<std::pair<int32_t, int32_t>> q;

    int32_t n, m, res = 0;
    std::cin >> n >> m;

    visited.resize(n);
    map.resize(n);
    for (int32_t i = 0; i < n; ++i) {
        std::cin >> map[i];
        visited[i].resize(m);
    }

    for (int32_t i = 0; i < n; ++i) {
        for (int32_t j = 0; j < m; ++j) {
            if (map[i][j] == '.' && !visited[i][j]) {
                ++res;

                visited[i][j] = true;
                q.push({i, j});

                while (!q.empty()) {
                    auto [x, y] = q.front();
                    q.pop();
                    
                    for (int32_t i = 0; i < 4; ++i) {
                        int32_t nx = x + dx[i];
                        int32_t ny = y + dy[i];

                        if (nx >= 0 && nx < n && ny >= 0 && ny < m &&
                            map[nx][ny] == '.' && !visited[nx][ny]) {
                            
                            visited[nx][ny] = true;
                            q.push({nx, ny});
                        }
                    }
                }
            }
        }
    }

    std::cout << res << "\n";
    return 0;
}