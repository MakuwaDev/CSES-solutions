#include <iostream>
#include <cstdint>
#include <vector>

constexpr int32_t INF = 1e7 + 9;

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::vector<int32_t> coins;
    std::vector<int32_t> dp;

    int32_t n, x;
    std::cin >> n >> x;

    coins.resize(n);
    for (auto it = coins.begin(); it != coins.end(); ++it) {
        std::cin >> *it;
    }

    dp.resize(x + 1);
    std::fill(dp.begin(), dp.end(), INF);
    dp[0] = 0;

    for (auto const& coin : coins) {
        for (int32_t sum = coin; sum <= x; ++sum) {
            dp[sum] = std::min(dp[sum], dp[sum - coin] + 1);
        }
    }

    if (dp[x] == INF) {
        std::cout << "-1\n";
    } else {
        std::cout << dp[x] << "\n";
    }
    return 0;
}