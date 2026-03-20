#include <iostream>
#include <array>

constexpr std::size_t MAXN = 1e6 + 6;
constexpr std::size_t MOD = 1e9 + 7;

constexpr std::size_t solid = 0;
constexpr std::size_t split = 1;

std::array<std::array<std::size_t, 2>, MAXN> dp;

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::size_t t, n;

    std::cin >> t;

    dp[1][solid] = dp[1][split] = 1;

    for (std::size_t i = 2; i < MAXN; ++i) {
        dp[i][solid] = (1 * dp[i - 1][split] + 2 * dp[i - 1][solid]) % MOD;
        dp[i][split] = (4 * dp[i - 1][split] + 1 * dp[i - 1][solid]) % MOD;
    }

    while (t--) {
        std::cin >> n;
        std::cout << (dp[n][split] + dp[n][solid]) % MOD << "\n";
    }

    return 0;
}