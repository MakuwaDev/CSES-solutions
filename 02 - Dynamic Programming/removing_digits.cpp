#include <iostream>
#include <vector>

constexpr std::size_t INF = 1e7 + 9;

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::vector<std::size_t> dp;

    std::size_t n;
    std::cin >> n;

    dp.resize(n + 1);
    std::fill(dp.begin(), dp.end(), INF);
    dp[0] = 0;

    for (std::size_t i = 1; i <= n; ++i) {
        std::size_t x = i;

        while (x) {
            std::size_t move = x % 10;
            dp[i] = std::min(dp[i], dp[i - move] + 1);
            x /= 10;
        }
    }

    std::cout << dp[n] << "\n";
}