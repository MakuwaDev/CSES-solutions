#include <iostream>
#include <vector>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::size_t n, k;
    std::vector<std::size_t> moves;
    std::vector<bool> dp;

    std::cin >> n >> k;

    dp.resize(n + 1, false);
    moves.resize(k);

    for (auto& m : moves) {
        std::cin >> m;
    }

    dp[0] = false;

    for (std::size_t i = 1; i <= n; ++i) {
        for (auto const& m : moves) {
            if (i >= m && !dp[i - m]) {
                dp[i] = true;
            }
        }

        std::cout << (dp[i] ? 'W' : 'L');
    }

    std::cout << "\n";
    return 0;
}