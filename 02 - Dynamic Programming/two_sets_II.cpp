#include <iostream>
#include <cstdint>
#include <vector>
#include <algorithm>

constexpr std::size_t MOD = 1e9 + 7;
constexpr std::size_t INV2 = 500000004;

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::vector<std::size_t> curr;
    std::vector<std::size_t> prev;
    std::size_t n, s;

    std::cin >> n;

    s = n * (n + 1) / 2;
    if (s % 2 == 1) {
        std::cout << "0\n";
        return 0;
    }

    prev.resize(2 * s + 1);
    curr.resize(2 * s + 1);
    curr[s] = 1;

    for (std::size_t x = 1; x <= n; ++x) {
        std::swap(curr, prev);
        std::fill(curr.begin(), curr.end(), 0);

        for (std::size_t i = x; i < curr.size(); ++i) {
            curr[i] = (curr[i] + prev[i - x]) % MOD;
        }

        for (std::size_t i = curr.size() - 1 - x; i < curr.size(); --i) {
            curr[i] = (curr[i] + prev[i + x]) % MOD;
        }
    }

    std::cout << (curr[s] * INV2) % MOD << "\n";
    return 0;
}