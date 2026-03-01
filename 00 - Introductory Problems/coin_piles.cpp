#include <iostream>
#include <cstdint>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    uint32_t t, a, b, sum;
    std::cin >> t;

    while (t--) {
        std::cin >> a >> b;
        if (a < b) {
            std::swap(a, b);
        }

        sum = a + b;
        if (sum % 3 == 0 && a <= 2 * sum / 3 && b >= sum / 3) {
            std::cout << "YES\n";
        } else {
            std::cout << "NO\n";
        }
    }

    return 0;
}