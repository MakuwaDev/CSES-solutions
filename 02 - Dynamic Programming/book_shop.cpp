#include <iostream>
#include <vector>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::vector<std::size_t> dp;
    std::vector<std::size_t> price;
    std::vector<std::size_t> pages;

    std::size_t n, x;
    std::cin >> n >> x;

    price.resize(n);
    pages.resize(n);
    dp.resize(x + 1);

    for (std::size_t i = 0; i < n; ++i) {
        std::cin >> price[i];
    }

    for (std::size_t i = 0; i < n; ++i) {
        std::cin >> pages[i];
    }

    for (std::size_t i = 0; i < n; ++i) {
        for (std::size_t j = x; j > 0; --j) {
            if (j >= price[i]) {
                dp[j] = std::max(dp[j], dp[j - price[i]] + pages[i]);
            }
        }
    }

    std::cout << dp[x] << "\n";
    return 0;
}