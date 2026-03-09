#include <iostream>
#include <vector>

constexpr std::size_t MOD = 1e9 + 7;

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::vector<std::size_t> val;
    std::vector<std::size_t> prev, curr;

    std::size_t n, ub, res = 0;
    std::cin >> n >> ub;

    val.resize(n);
    prev.resize(ub + 2);
    curr.resize(ub + 2);

    for (auto& v : val) {
        std::cin >> v;
    }

    if (val[0]) {
        curr[val[0]] = 1;
    } else {
        for (std::size_t i = 1; i <= ub; ++i) {
            curr[i] = 1;
        }
    }

    for (std::size_t i = 1; i < n; ++i) {
        std::swap(prev, curr);

        if (val[i]) {
            std::size_t j = val[i];
            std::fill(curr.begin(), curr.end(), 0);

            curr[j] = 0;
            curr[j] = (curr[j] + prev[j - 1]) % MOD;
            curr[j] = (curr[j] + prev[j]) % MOD;
            curr[j] = (curr[j] + prev[j + 1]) % MOD; 

        } else {
            for (std::size_t j = 1; j <= ub; ++j) {
                curr[j] = 0;
                curr[j] = (curr[j] + prev[j - 1]) % MOD;
                curr[j] = (curr[j] + prev[j]) % MOD;
                curr[j] = (curr[j] + prev[j + 1]) % MOD; 
            }
        }
    }

    for (std::size_t i = 0; i <= ub; ++i) {
        res = (res + curr[i]) % MOD;
    }

    std::cout << res << "\n";
    return 0;
}