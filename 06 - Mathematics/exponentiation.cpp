#include <iostream>

constexpr std::size_t MOD = 1e9 + 7;

constexpr std::size_t pow_mod(std::size_t x, std::size_t exp, std::size_t mod) {
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

    std::size_t q, a, b;

    std::cin >> q;

    while (q--) {
        std::cin >> a >> b;
        std::cout << pow_mod(a, b, MOD) << "\n";
    }

    return 0;
}