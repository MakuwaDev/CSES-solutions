#include <iostream>
#include <array>

constexpr std::size_t MAX = 1e6 + 6;
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

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    fact_mod[0] = 1;
    for (std::size_t i = 1; i < MAX; ++i) {
        fact_mod[i] = (fact_mod[i - 1] * i) % MOD;
    }

    std::array<std::size_t, 26> counts{};
    std::string s;
    std::size_t nominator, denominator = 1;
    
    std::cin >> s;
    nominator = fact_mod[s.size()];

    for (auto const& c : s) {
        ++counts[c - 'a'];
    }

    for (auto const& c : counts) {
        denominator = (denominator * fact_mod[c]) % MOD;
    }

    std::cout << (nominator * pow_mod(denominator, MOD - 2)) % MOD << "\n";
    return 0;
}