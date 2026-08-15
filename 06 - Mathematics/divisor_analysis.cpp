#include <iostream>
#include <cstdint>
#include <vector>
#include <ranges>

constexpr int64_t MOD = 1e9 + 7;
constexpr int64_t MOD_EXP = MOD - 1;

constexpr int64_t fastpow(int64_t x, int64_t exp) {
    int64_t res = 1, pow = x;

    while (exp > 0) {
        if (exp & 1) {
            res = (res * pow) % MOD;
        }

        pow = (pow * pow) % MOD;
        exp >>= 1;
    }

    return res;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::size_t n;
    int64_t p, k, num = 1, sum = 1, numerator, denominator, prod = 1, d = 1, x, pow;

    std::cin >> n;

    while (n--) {
        std::cin >> p >> k;

        num = (num * (k + 1)) % MOD;

        numerator = ((fastpow(p, k + 1) - 1) + MOD) % MOD;
        denominator = fastpow(p - 1, MOD - 2);
        sum = (sum * ((numerator * denominator) % MOD)) % MOD;

        x = k & 1 ? (k * ((k + 1) / 2)) % MOD_EXP : ((k / 2) * (k + 1)) % MOD_EXP;
        pow = (d * x) % MOD_EXP;
        prod = (fastpow(prod, k + 1) * fastpow(p, pow)) % MOD;
        d = (d * (k + 1)) % MOD_EXP;
    }

    std::cout << num << " " << sum << " " << prod << "\n";
    return 0;
}