#include <iostream>

constexpr std::size_t MOD = 1e9 +7;

std::size_t gcd(std::size_t a, std::size_t b) {
    if (a == 0) {
        return b;
    }

    return gcd(b % a, a);
}

std::size_t pow_mod(std::size_t x, std::size_t exp, std::size_t mod) {
    std::size_t res = 1, pow = x;

    while (exp > 0) {
        if (exp & 1) {
            res = (res * pow) % mod;
        }

        pow = (pow * pow) % mod;
        exp >>= 1;
    }

    return res;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::size_t n, m, res = 0;

    std::cin >> n >> m;

    for (std::size_t k = 0; k < n; ++k) {
        res = (res + pow_mod(m, gcd(n, k), MOD)) % MOD;
    }

    res = (res * pow_mod(n, MOD - 2, MOD)) % MOD;

    std::cout << res << "\n";
    return 0;
}