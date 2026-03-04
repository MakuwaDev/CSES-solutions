#include <iostream>
#include <vector>

constexpr std::size_t MOD = 1e9 + 7;

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::vector<std::size_t> coins;
    std::vector<std::size_t> dp;

    std::size_t n, x;
    std::cin >> n >> x;

    coins.resize(n);
    for (auto it = coins.begin(); it != coins.end(); ++it) {
        std::cin >> *it;
    }

    dp.resize(x + 1);
    std::fill(dp.begin(), dp.end(), 0);
    dp[0] = 1;

    for (auto const& coin : coins) {
        for (std::size_t sum = coin; sum <= x; ++sum) {
            dp[sum] = (dp[sum] + dp[sum - coin]) % MOD;
        }
    }

    std::cout << dp[x] % MOD << "\n";
    return 0;
}