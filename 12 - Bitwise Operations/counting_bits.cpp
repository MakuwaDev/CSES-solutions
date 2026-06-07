#include <iostream>
#include <vector>
#include <cstdint>

int64_t dp[60][2][60];
std::vector<int32_t> bits;

int64_t solve(int32_t i, bool tight, int64_t cnt) {
    if (i < 0) {
        return cnt;
    }

    if (dp[i][tight][cnt] != -1) {
        return dp[i][tight][cnt];
    }

    int32_t limit = tight ? bits[i] : 1;
    int64_t total = 0;

    for (int32_t d = 0; d <= limit; ++d) {
        total += solve(i - 1, tight && (d == limit), cnt + (d == 1));
    }

    return dp[i][tight][cnt] = total;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int64_t n;

    std::cin >> n;

    if (n == 0) {
        std::cout << "0\n";
        return 0;
    }

    for (std::size_t i = 0; i < 60; ++i) {
        for (std::size_t j = 0; j < 2; ++j) {
            for (std::size_t k = 0; k < 60; ++k) {
                dp[i][j][k] = -1;
            }
        }
    }

    while (n > 0) {
        bits.push_back(n % 2);
        n /= 2;
    }

    std::cout << solve(bits.size() - 1, true, 0);
}