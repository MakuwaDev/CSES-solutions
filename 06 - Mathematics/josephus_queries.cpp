#include <iostream>

std::size_t josephus(std::size_t n, std::size_t k) {
    if (n == 1) {
        return 1;
    }

    if (k <= n / 2) {
        return 2 * k;
    }

    if (n & 1) {
        std::size_t p = josephus(n / 2 + 1, k - n / 2);

        if (p == 1) {
            return n;
        } else {
            return 2 * p - 3;
        }
    } else {
        return 2 * josephus(n / 2, k - n / 2) - 1;
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::size_t q, n, k;

    std::cin >> q;

    while (q--) {
        std::cin >> n >> k;
        std::cout << josephus(n, k) << "\n";
    }
}