#include <iostream>
#include <vector>
#include <numeric>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::vector<std::size_t> arr;
    std::vector<std::size_t> pref;
    std::size_t n, q, a, b;

    std::cin >> n >> q;

    arr.resize(n);
    pref.resize(n);
    for (auto& x : arr) {
        std::cin >> x;
    }

    std::inclusive_scan(arr.begin(), arr.end(), pref.begin(), [](std::size_t x, std::size_t y) {
        return x ^ y;
    });

    while (q--) {
        std::cin >> a >> b;
        --a; --b;

        std::cout << (pref[b] ^ (a > 0 ? pref[a - 1] : 0)) << "\n";
    }

    return 0;
}