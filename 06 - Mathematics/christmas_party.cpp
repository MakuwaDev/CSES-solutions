#include <iostream>
#include <vector>

constexpr std::size_t MOD = 1e9 + 7;

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::vector<std::size_t> res;
    std::size_t n;

    std::cin >> n;

    if (n == 1) {
        std::cout << "0\n";
        return 0;
    }

    res.resize(n + 1);
    res[1] = 0;
    res[2] = 1;

    for (std::size_t i = 3; i <= n; ++i) {
        res[i] = ((i - 1) * ((res[i - 1] + res[i - 2]) % MOD)) % MOD;
    }

    std::cout << res[n] << "\n";
    return 0;
}