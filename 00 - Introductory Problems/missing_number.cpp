#include <iostream>
#include <cstdint>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    uint64_t n, sum = 0, x;
    std::cin >> n;

    for (uint64_t i = 1; i < n; ++i) {
        std::cin >> x;
        sum += x;
    }

    std:: cout << (n * (n + 1) / 2) - sum << "\n";
}
