#include <iostream>
#include <cstdint>
#include <array>
#include <string>

constexpr std::size_t MOVE_COUNT = 4;
constexpr std::array<int32_t, MOVE_COUNT> dr = {1, -1, 0, 0};
constexpr std::array<int32_t, MOVE_COUNT> dc = {0, 0, 1, -1};
constexpr std::array<char, MOVE_COUNT> ds = {'D', 'U', 'R', 'L'};

std::array<std::array<bool, 9>, 9> vis;
std::string s;

std::size_t backtrack(std::size_t r, std::size_t c, std::size_t step) {
    if (r == 7 && c == 1) {
        return (step == 48) ? 1 : 0;
    }
    
    if (step == 48) {
        return 0;
    }
    
    if (vis[r - 1][c] && vis[r + 1][c] && !vis[r][c - 1] && !vis[r][c + 1]) {
        return 0;
    }

    if (vis[r][c - 1] && vis[r][c + 1] && !vis[r - 1][c] && !vis[r + 1][c]) {
        return 0;
    }
    
    vis[r][c] = true;
    std::size_t paths = 0;
    
    if (s[step] == '?') {
        for (std::size_t i = 0; i < 4; ++i) {
            int32_t nr = r + dr[i];
            int32_t nc = c + dc[i];
            if (!vis[nr][nc]) {
                paths += backtrack(nr, nc, step + 1);
            }
        }
    } else {
        for (std::size_t i = 0; i < 4; ++i) {
            if (s[step] == ds[i]) {
                int32_t nr = r + dr[i];
                int32_t nc = c + dc[i];
                if (!vis[nr][nc]) {
                    paths += backtrack(nr, nc, step + 1);
                }
            }
        }
    }
    
    vis[r][c] = false;
    return paths;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    std::cin >> s;
    
    for (std::size_t i = 0; i < 9; ++i) {
        for (std::size_t j = 0; j < 9; ++j) {
            vis[i][j] = false;
        }
    }
    
    for (std::size_t i = 0; i < 9; ++i) {
        vis[0][i] = true;
        vis[8][i] = true;
        vis[i][0] = true;
        vis[i][8] = true;
    }
    
    std::cout << backtrack(1, 1, 0) << "\n";
    return 0;
}