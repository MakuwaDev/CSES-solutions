#include <iostream>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::size_t t, n, a, b;

    std::cin >> t;
    while (t--) {
        std::cin >> n >> a >> b;

        if (a + b > n) {
            std::cout << "NO\n";
            continue;
        }

        if ((a == 0 || b == 0) && (a + b > 0)) {
            std::cout << "NO\n";
            continue;
        }

        std::cout << "YES\n";

        for (std::size_t i = 1; i <= n; ++i) {
            std::cout << i << " ";
        }

        std::cout << "\n";

        for (std::size_t i = 1; i <= n - a - b; ++i) {
            std::cout << i << " ";
        }

        for (std::size_t i = 0; i < a + b; ++i) {
            std::cout << (n - a - b + 1) + (i + a) % (a + b) << " ";
        }

        std::cout << "\n";
    }

    return 0;
}