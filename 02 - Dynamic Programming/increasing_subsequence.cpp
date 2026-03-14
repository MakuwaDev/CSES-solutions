#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

constexpr std::size_t INF = std::numeric_limits<std::size_t>::max();

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::vector<std::size_t> a;
    std::vector<std::size_t> dp;
    std::size_t n;
    
    std::cin >> n;
    a.resize(n);
    dp.resize(n + 1, INF);

    for (auto& x : a) {
        std::cin >> x;
    }

    dp[0] = 0;
    for (auto const& x : a) {
        auto i = std::upper_bound(dp.begin(), dp.end(), x) - dp.begin();
        
        if (dp[i - 1] < x) {
            dp[i] = x;
        }
    }

    for (std::size_t i = n; i > 0; --i) {
        if (dp[i] != INF) {
            std::cout << i << "\n";
            break;
        }
    }

    return 0;
}