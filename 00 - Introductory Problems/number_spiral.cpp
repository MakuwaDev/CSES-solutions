#include <iostream>
#include <cstdint>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    uint64_t t, y, x;
    std::cin >> t;

    for (uint32_t i = 0; i < t; ++i) {
        std::cin >> y >> x;

        if (x == y) {
            std::cout << 1 + x * (x - 1);
        } else if (x > y) {
            uint64_t diff = x - y;
            uint64_t mid = 1 + x * (x - 1);
            std::cout << (x & 1 ? mid + diff : mid - diff);
        } else {
            uint64_t diff = y - x;
            uint64_t mid = 1 + y * (y - 1);
            std::cout << (y & 1 ? mid - diff : mid + diff);
        }

        std::cout << "\n";
    }
}