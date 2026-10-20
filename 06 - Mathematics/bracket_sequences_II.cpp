#include <iostream>
#include <string>
#include <cstdint>
#include <array>

constexpr int64_t MAX = 1e6 + 6;
constexpr int64_t MOD = 1e9 + 7;

std::array<int64_t, MAX> fact_mod;

int64_t pow_mod(int64_t x, int64_t exp) {
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

int64_t rev_mod(int64_t x) {
    return pow_mod(x, MOD - 2);
}

int64_t newton_mod(int64_t a, int64_t b) {
    return (fact_mod[a] * rev_mod((fact_mod[b] * fact_mod[a - b]) % MOD) % MOD) % MOD;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    fact_mod[0] = 1;
    for (int64_t i = 1; i < MAX; ++i) {
        fact_mod[i] = (fact_mod[i - 1] * i) % MOD;
    }

    int64_t n, oc = 0, cc = 0, rem_len, rem_open;
    std::string pref;

    std::cin >> n >> pref;

    if (n & 1) {
        std::cout << "0\n";
        return 0;
    }

    for (auto const& c : pref) {
        if (c == '(') {
            ++oc;
        } else {
            ++cc;
        }

        if (cc > oc) {
            std::cout << "0\n";
            return 0;
        }
    }

    if (oc > n /2 || cc > n / 2) {
        std::cout << "0\n";
        return 0;
    }

    rem_len = n - static_cast<int64_t>(pref.size());
    rem_open = n / 2 - oc;

    std::cout << (newton_mod(rem_len, rem_open) - newton_mod(rem_len, rem_open - 1) + MOD) % MOD << "\n";

    return 0;
}