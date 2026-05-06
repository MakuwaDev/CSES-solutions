#include <iostream>
#include <vector>

constexpr std::size_t MOD = 1e9 + 7;

std::vector<std::vector<std::size_t>> dp;
std::size_t n, m;

void backtrack(std::size_t c, std::size_t r, std::size_t curr, std::size_t next) {
    if (r == n) {
        dp[c + 1][next] = (dp[c + 1][next] + dp[c][curr]) % MOD;
        return;
    }

    if (curr & (1 << r)) {
        backtrack(c, r + 1, curr, next);
    } else {
        backtrack(c, r + 1, curr, next | (1 << r));

        if (r + 1 < n && !(curr & (1 << (r + 1)))) {
            backtrack(c, r + 2, curr, next);
        }
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cin >> n >> m;

    dp.resize(m + 1);
    for (auto& v : dp) {
        v.resize(1 << n);
    }

    dp[0][0] = 1;

    for (std::size_t i = 0; i < m; ++i) {
        for (std::size_t mask = 0; mask < (1ull << n); ++mask) {
            if (dp[i][mask] > 0) {
                backtrack(i, 0, mask, 0);
            }
        }
    }

    std::cout << dp[m][0] << "\n";
    return 0;
}