#include <iostream>

constexpr std::size_t MOD = 1e9 + 7;
constexpr std::size_t INV2 = 500000004;

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::size_t n, res = 0, i = 1, j, q, rangeQ;

    std::cin >> n;

    for (; i <= n; i = j) {
        q = n / i;
        j = n / q + 1;

        rangeQ = ((((i % MOD + (j - 1) % MOD) % MOD * ((j - i) % MOD)) % MOD) * INV2) % MOD;
        res = (res + (q % MOD) * rangeQ) % MOD;
    }

    std::cout << res << "\n";
    return 0;
}