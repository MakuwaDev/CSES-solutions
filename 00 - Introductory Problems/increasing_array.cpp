#include <iostream>
#include <vector>
#include <cstdint>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    uint32_t n;
    uint64_t res = 0;
    std::cin >> n;

    std::vector<uint64_t> x(n);

    for (uint32_t i = 0; i < n; ++i) {
        std::cin >> x[i];
    }

    for (uint32_t i = 1; i < n; ++i) {
        if (x[i] < x[i - 1]) {
            res += x[i - 1] - x[i];
            x[i] = x[i - 1];
        }
    }

    std::cout << res << "\n";

    return 0;
}
