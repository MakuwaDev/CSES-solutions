#include <iostream>
#include <array>

constexpr std::size_t MAXX = 1e6 + 6;

std::array<std::size_t, MAXX> divisors;

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::size_t n, x;

    for (std::size_t i = 1; i < MAXX; ++i) {
        for (std::size_t j = i; j < MAXX; j += i) {
            ++divisors[j];
        }
    }

    std::cin >> n;

    while (n--) {
        std::cin >> x;
        std::cout << divisors[x] << "\n";
    }

    return 0;
}