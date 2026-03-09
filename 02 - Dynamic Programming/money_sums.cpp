#include <iostream>
#include <vector>
#include <numeric>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::vector<std::size_t> coins;
    std::vector<std::size_t> achieved;
    std::vector<bool> dp;

    std::size_t n, sum;
    std::cin >> n;

    coins.resize(n);
    for (auto& c : coins) {
        std::cin >> c;
    }

    sum = std::accumulate(coins.begin(), coins.end(), 0);
    dp.resize(sum + 1);
    dp[0] = true;

    for (auto const& c : coins) {
        for (std::size_t i = sum; i >= c; --i) {
            dp[i] = dp[i] | dp[i - c];
        }
    }

    for (std::size_t i = 1; i <= sum; ++i) {
        if (dp[i]) {
            achieved.push_back(i);
        }
    }

    std::cout << achieved.size() << "\n";
    for (auto const& x : achieved) {
        std::cout << x << " ";
    }

    std::cout << "\n";
    return 0;
}