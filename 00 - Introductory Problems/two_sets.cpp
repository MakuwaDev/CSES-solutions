#include <iostream>
#include <cstdint>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    uint32_t n;
    std::cin >> n;

    if (n % 4 == 0) {
        std::cout << "YES\n" << n / 2 << "\n";

        for (uint32_t i = 1; i <= n; i += 4) {
            std::cout << i << " " << i + 3 << " ";
        }

        std::cout << "\n" << n / 2 << "\n";

        for (uint32_t i = 2; i <= n; i += 4) {
            std::cout << i << " " << i + 1 << " ";
        }
    } else if (n % 4 == 3) {
        std::cout << "YES\n" << n / 2 + 1 << "\n1 2 ";

        for (uint32_t i = 4; i <= n; i += 4) {
            std::cout << i << " " << i + 3 << " ";
        }

        std::cout << "\n" << n / 2 << "\n3 ";

        for (uint32_t i = 5; i <= n; i += 4) {
            std::cout << i << " " << i + 1 << " ";
        }
    } else {
        std::cout << "NO\n";
        return 0;
    }

    std::cout << "\n";
    return 0;
}