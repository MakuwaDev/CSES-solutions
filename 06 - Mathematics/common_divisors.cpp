#include <iostream>
#include <array>

constexpr std::size_t MAX_X = 1e6 + 7;

std::array<std::size_t, MAX_X> cnt;

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::size_t n, x;

    std::cin >> n;
    while (n--) {
        std::cin >> x;
        ++cnt[x];
    }

    for (std::size_t gcd = MAX_X - 1; gcd > 0; --gcd) {
        x = 0;

        for (std::size_t m = gcd; m < MAX_X; m += gcd) {
            x += cnt[m];
        }

        if (x >= 2) {
            std::cout << gcd << "\n";
            return 0;
        }
    }
}