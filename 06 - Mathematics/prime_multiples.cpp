#include <iostream>
#include <vector>
#include <cstdint>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::vector<std::size_t> primes;
    std::size_t n, k;
    int64_t res = 0;

    std::cin >> n >> k;

    primes.resize(k);
    for (auto& p : primes) {
        std::cin >> p;
    }

    for (std::size_t mask = 1; mask < (static_cast<std::size_t>(1) << k); ++mask) {
        bool overflow = false;
        std::size_t product = 1, bits = 0;

        for (std::size_t i = 0; i < k; ++i) {
            if (mask & (1 << i)) {
                ++bits;

                if (product > n / primes[i]) {
                    overflow = true;
                    break;
                }

                product *= primes[i];
            }
        }

        if (overflow) {
            continue;
        }

        res += bits % 2 ? (n / product) : -(n / product);
    }

    std::cout << res << "\n";
    return 0;
}