#include <iostream>
#include <vector>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::vector<std::vector<std::size_t>> dp;
    std::size_t n, m;

    std::cin >> n >> m;

    dp.resize(n + 1);
    for (auto& v : dp) {
        v.resize(m + 1, n * m + 1);
    }

    for (std::size_t i = 1; i <= n; ++i) {
        for (std::size_t j = 1; j <= m; ++j) {
            if (i == j) {
                dp[i][j] = 0;
                continue;
            }

            for (std::size_t k = 1; k < i; ++k) {
                dp[i][j] = std::min(dp[i][j], dp[k][j] + dp[i - k][j] + 1);
            }

            for (std::size_t k = 1; k < j; ++k) {
                dp[i][j] = std::min(dp[i][j], dp[i][k] + dp[i][j - k] + 1);
            }
        }
    }

    std::cout << dp[n][m] << "\n";
    return 0;
}