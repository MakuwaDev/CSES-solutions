#include <iostream>
#include <cstdint>

inline char nth_champernowne_digit(uint64_t n) {
    uint64_t length = 1, count = 9, start = 1, target_number, target_digit;

    while (count * length < n) {
        n -= count * length;
        count *= 10;
        start *= 10;
        ++length;
    }

    target_number = start + (n - 1) / length;
    target_digit = (n - 1) % length;

    for (uint64_t i = 0; i < length - target_digit - 1; ++i) {
        target_number /= 10;
    }

    return static_cast<char>(target_number % 10 + '0');
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    uint64_t n, q;
    std::cin >> n;

    while (n--) {
        std::cin >> q;
        std::cout << nth_champernowne_digit(q) << "\n";
    }
}