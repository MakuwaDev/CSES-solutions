#include <iostream>
#include <cstdint>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    uint64_t n;
    std::cin >> n;

    for (uint64_t k = 1; k <= n; ++k) {
        std::cout << k * k * (k * k - 1) / 2 - 4 * (k - 1) * (k - 2) << "\n";
    }
}