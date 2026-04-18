#include <iostream>
#include <vector>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::vector<std::size_t> weights;
    std::vector<std::pair<std::size_t, std::size_t>> dp;
    std::size_t n, x;
    
    std::cin >> n >> x;
    weights.resize(n);
    dp.resize(1 << n);

    for (auto& w : weights) {
        std::cin >> w;
    }

    dp[0] = {1, 0};
    for (std::size_t mask = 1; mask < (1ull << n); ++mask) {
        dp[mask] = {n + 1, 0};

        for (std::size_t p = 0; p < n; ++p) {
            if (mask & (1 << p)) {
                auto [r, c] = dp[mask ^ (1 << p)];

                if (c + weights[p] <= x) {
                    c += weights[p];
                } else {
                    ++r;
                    c = weights[p];
                }

                dp[mask] = std::min(dp[mask], {r, c});
            }
        }
    }

    std::cout << dp[(1 << n) - 1].first << "\n";
    return 0;
}