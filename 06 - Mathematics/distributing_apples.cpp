#include <iostream>
#include <array>

constexpr std::size_t MAX = 2e6 + 6;
constexpr std::size_t MOD = 1e9 + 7;

std::array<std::size_t, MAX> fact_mod;

std::size_t pow_mod(std::size_t x, std::size_t exp) {
    std::size_t res = 1, pow = x;

    while (exp > 0) {
        if (exp & 1) {
            res = (res * pow) % MOD;
        }

        pow = (pow * pow) % MOD;
        exp >>= 1;
    }

    return res;
}

std::size_t newton_mod(std::size_t a, std::size_t b) {
    return (fact_mod[a] * pow_mod((fact_mod[b] * fact_mod[a - b]) % MOD, MOD - 2)) % MOD;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    fact_mod[0] = 1;
    for (std::size_t i = 1; i < MAX; ++i) {
        fact_mod[i] = (fact_mod[i - 1] * i) % MOD;
    }

    std::size_t n, m;
    std::cin >> n >> m;
    std::cout << newton_mod(n + m - 1, n - 1) << "\n";
    return 0;
}