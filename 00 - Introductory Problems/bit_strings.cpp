#include <iostream>
#include <cstdint>

constexpr uint64_t MOD = 1e9 + 7;

uint64_t power_modulo(uint64_t base, uint64_t exp, uint64_t mod) {
    uint64_t res = 1;
    base %= mod;

    while (exp > 0) {
        if (exp & 1) {
            res = (res * base) % mod;
        }

        base = (base * base) % mod;
        exp >>= 1;
    }

    return res;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    uint64_t n;
    std::cin >> n;

    std::cout << power_modulo(2, n, MOD);
}