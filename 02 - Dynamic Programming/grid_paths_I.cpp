#include <iostream>
#include <vector>

constexpr std::size_t MOD = 1e9 + 7;

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::vector<std::string> grid;
    std::vector<std::vector<std::size_t>> dp;

    std::size_t n;
    std::cin >> n;

    grid.resize(n);
    dp.resize(n);

    for (std::size_t i = 0; i < n; ++i) {
        std::cin >> grid[i];
        dp[i].resize(n);
    }

    dp[0][0] = grid[0][0] == '.' ? 1 : 0;
    for (std::size_t i = 1; i < n; ++i) {
        dp[i][0] = grid[i][0] == '.' ? dp[i - 1][0] : 0;
        dp[0][i] = grid[0][i] == '.' ? dp[0][i - 1] : 0;
    }

    for (std::size_t i = 1; i < n; ++i) {
        for (std::size_t j = 1; j < n; ++j) {
            dp[i][j] = grid[i][j] == '.' ? (dp[i - 1][j] + dp[i][j - 1]) % MOD : 0;
        }
    }

    std::cout << dp[n - 1][n - 1] % MOD << "\n";
    return 0;
}