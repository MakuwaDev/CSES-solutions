#include <iostream>
#include <vector>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::vector<std::size_t> a, b, res;
    std::vector<std::vector<std::size_t>> dp;
    std::size_t n, m;

    std::cin >> n >> m;

    a.resize(n);
    b.resize(m);

    dp.resize(n + 1);
    for (auto& v : dp) {
        v.resize(m + 1);
    }

    for (auto& x : a) {
        std::cin >> x;
    }

    for (auto& x : b) {
        std::cin >> x;
    }

    for (std::size_t i = 1; i <= n; ++i) {
        for (std::size_t j = 1; j <= m; ++j) {
            if (a[i - 1] == b[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            } else {
                dp[i][j] = std::max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }

    std::cout << dp[n][m] << "\n";

    while (n > 0 && m > 0) {
        if (a[n - 1] == b[m - 1]) {
            res.push_back(a[n - 1]);
            --n;
            --m;
        } else if (dp[n - 1][m] > dp[n][m - 1]) {
            --n;
        } else {
            --m;
        }
    }

    for (auto it = res.rbegin(); it != res.rend(); ++it) {
        std::cout << *it << " ";
    }

    std::cout << "\n";
    return 0;
}