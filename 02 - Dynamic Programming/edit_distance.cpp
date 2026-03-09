#include <iostream>
#include <vector>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::vector<std::vector<std::size_t>> dp;
    std::size_t n, m;
    std::string a, b;
    bool used;

    std::cin >> a >> b;

    n = a.size();
    m = b.size();

    dp.resize(n);
    for (auto& x : dp) {
        x.resize(m);
    }

    used = false;
    for (std::size_t i = 0; i < n; ++i) {
        dp[i][0] = i + 1;

        if (a[i] == b[0] || used) {
            --dp[i][0];
            used = true;
        }
    }

    used = false;
    for (std::size_t j = 0; j < m; ++j) {
        dp[0][j] = j + 1;

        if (a[0] == b[j] || used) {
            --dp[0][j];
            used = true;
        }
    }

    for (std::size_t i = 1; i < n; ++i) {
        for (std::size_t j = 1; j < m; ++j) {
            dp[i][j] = std::min(dp[i - 1][j] + 1, dp[i][j - 1] + 1);

            if (a[i] == b[j]) {
                dp[i][j] = std::min(dp[i][j], dp[i - 1][j - 1]);
            } else {
                dp[i][j] = std::min(dp[i][j], dp[i - 1][j - 1] + 1);
            }
        }
    }

    std::cout << dp[n - 1][m - 1] << "\n";
    return 0;
}