#include <iostream>
#include <cstdint>
#include <vector>
#include <algorithm>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::vector<uint32_t> weights;
    std::size_t n, res = 0, h, l;
    uint32_t limit;

    std::cin >> n >> limit;
    weights.resize(n);
    for (std::size_t i = 0; i < n; ++i) {
        std::cin >> weights[i];
    }

    std::sort(weights.begin(), weights.end());
    h = n - 1;
    l = 0;

    while (h >= l && h < n) {
        if (weights[h] + weights[l] <= limit) {
            ++l;
        }

        ++res;
        --h;
    }

    std::cout << res << "\n";
}