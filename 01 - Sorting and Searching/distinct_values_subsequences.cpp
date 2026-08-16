#include <iostream>
#include <cstdint>
#include <map>

constexpr std::size_t MOD = 1e9 + 7;

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::size_t n, x, res = 1;
    std::map<uint32_t, std::size_t> cnt;

    std::cin >> n;

    while (n--) {
        std::cin >> x;
        ++cnt[x];
    }

    for (auto& it : cnt) {
        res = (res * (it.second + 1)) % MOD;
    }

    std::cout << res - 1 << "\n";
    return 0;
}