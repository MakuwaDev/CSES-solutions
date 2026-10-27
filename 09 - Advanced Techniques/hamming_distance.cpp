#include <iostream>
#include <string>
#include <vector>
#include <bitset>

constexpr std::size_t MAXK = 31;

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::size_t n, k, res = MAXK;
    std::string s;
    std::vector<std::bitset<MAXK>> arr;

    std::cin >> n >> k;

    arr.resize(n);
    for (std::size_t i = 0; i < n; ++i) {
        std::cin >> s;

        for (std::size_t j = 0; j < s.size(); ++j) {
            arr[i].set(j, s[j] == '1' ? 1 : 0);
        }
    }

    for (std::size_t i = 0; i < n; ++i) {
        for (std::size_t j = i + 1; j < n; ++j) {
            res = std::min(res, (arr[i] ^ arr[j]).count());
        }
    }

    std::cout << res << "\n";
    return 0;
}