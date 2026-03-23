#include <iostream>
#include <vector>
#include <cstdint>
#include <numeric>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::vector<int64_t> a;
    std::vector<int64_t> psum;
    std::vector<std::vector<int64_t>> dp;
    std::size_t n;

    std::cin >> n;
    a.resize(n);
    psum.resize(n);
    dp.resize(n);

    for (std::size_t i = 0; i < n; ++i) {
        std::cin >> a[i];
        dp[i].resize(n);
        dp[i][i] = a[i];
    }

    std::partial_sum(a.begin(), a.end(), psum.begin());

    for (std::size_t len = 2; len <= n; ++len) {
        for (std::size_t i = 0; i + len - 1 < n; ++i) {
            std::size_t j = i + len - 1;
            
            int64_t left = a[i] + (psum[j] - psum[i] - dp[i + 1][j]);
            int64_t right = a[j] + (psum[j - 1] - psum[i] + a[i] - dp[i][j - 1]);

            dp[i][j] = std::max(left, right);
        }
    }

    std::cout << dp[0][n - 1] << "\n";
    return 0;
}