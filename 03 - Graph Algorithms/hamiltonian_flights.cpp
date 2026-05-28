#include <iostream>
#include <vector>
#include <cstdint>

constexpr std::size_t MOD = 1e9 + 7;

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::vector<std::vector<uint32_t>> rev;
    std::vector<std::vector<std::size_t>> dp;
    uint32_t n, m, a, b;

    std::cin >> n >> m;

    rev.resize(n);
    dp.resize(1 << n);

    for (auto& v : dp) {
        v.resize(n);
    }

    while (m--) {
        std::cin >> a >> b;
        --a; --b;
        rev[b].push_back(a);
    }

    dp[1][0] = 1;

    for (uint32_t mask = 2; mask < (static_cast<uint32_t>(1) << n); ++mask) {
        if (!(mask & 1)) {
            continue;
        }

        if ((mask & (1 << (n - 1))) && mask != ((static_cast<uint32_t>(1) << n) - 1)) {
            continue;
        }

        for (uint32_t i = 0; i < n; ++i) {
            if (mask & (1 << i)) {
                for (auto const& j : rev[i]) {
                    dp[mask][i] = (dp[mask][i] + dp[mask ^ (1 << i)][j]) % MOD;
                }
            }
        }
    }

    std::cout << dp[(1 << n) - 1][n - 1] << "\n";
    return 0;
}