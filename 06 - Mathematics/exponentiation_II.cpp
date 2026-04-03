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

    std::size_t q, a, b, c, bc;
    
    std::cin >> q;
    
    while (q--) {
        std::cin >> a >> b >> c;
        bc = pow_mod(b, c, MOD - 1);
        std::cout << pow_mod(a, bc, MOD) << "\n";
    }

    return 0;
}