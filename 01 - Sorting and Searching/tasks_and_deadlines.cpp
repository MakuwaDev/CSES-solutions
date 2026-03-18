#include <iostream>
#include <cstdint>
#include <vector>
#include <algorithm>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::vector<int64_t> a;
    std::size_t n;
    int64_t d, f = 0, res = 0;

    std::cin >> n;
    a.resize(n);

    for (std::size_t i = 0; i < n; ++i) {
        std::cin >> a[i] >> d;
        res += d;
    }

    std::sort(a.begin(), a.end());

    for (auto const& x : a) {
        f += x;
        res -= f;
    }

    std::cout << res << "\n";
}