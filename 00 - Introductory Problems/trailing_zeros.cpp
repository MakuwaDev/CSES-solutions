#include <iostream>
#include <cstdint>
#include <cmath>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    uint64_t n, res = 0;
    std::cin >> n;

    while (n > 0) {
        res += n / 5;
        n /= 5;
    }

    std::cout << res << "\n";
}