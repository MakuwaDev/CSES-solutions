#include <iostream>
#include <vector>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::size_t n;
    std::string res;
    std::vector<std::string> grid;
    std::vector<std::pair<std::size_t, std::size_t>> active, next;
    std::vector<std::vector<bool>> vis;
    
    std::cin >> n;

    grid.resize(n);
    vis.resize(n, std::vector<bool>(n));

    for (auto& s : grid) {
        std::cin >> s;
    }

    res = grid[0][0];
    active = {{0, 0}};
    vis[0][0] = true;

    for (std::size_t k = 1; k < 2 * n - 1; ++k) {
        char small = 100;
        for (auto& [i, j] : active) {
            if (i + 1 < n) {
                small = std::min(small, grid[i + 1][j]);
            }

            if (j + 1 < n) {
                small = std::min(small, grid[i][j + 1]);
            }
        }

        res.push_back(small);

        for (auto& [i, j] : active) {
            if (i + 1 < n && grid[i + 1][j] == small && !vis[i + 1][j]) {
                next.push_back({i + 1, j});
                vis[i + 1][j] = true;
            }

            if (j + 1 < n && grid[i][j + 1] == small && !vis[i][j + 1]) {
                next.push_back({i, j + 1});
                vis[i][j + 1] = true;
            }
        }

        std::swap(active, next);
        next.clear();
    }

    std::cout << res << "\n";
    return 0;
}