#include <iostream>
#include <vector>
#include <cstdint>

constexpr uint64_t MOD = 1e9 + 7;

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::vector<uint64_t> ways;

    uint32_t n;
    std::cin >> n;

    ways.resize(n + 1);
    ways[0] = 1;
    
    for (uint32_t i = 1; i <= n; ++i) {
        for (uint32_t j = 1; j <= 6; ++j) {
            if (i >= j) {
                ways[i] = (ways[i] + ways[i - j]) % MOD;
            }
        }
    }

    std::cout << ways[n] << "\n";
    return 0;
}