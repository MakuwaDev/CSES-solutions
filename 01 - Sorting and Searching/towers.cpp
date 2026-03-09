#include <iostream>
#include <cstdint>
#include <vector>
#include <algorithm>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::vector<uint32_t> towers;

    uint32_t n, x;
    std::cin >> n;

    while (n--) {
        std::cin >> x;
        auto it = std::upper_bound(towers.begin(), towers.end(), x);

        if (it != towers.end()) {
            *it = x;
        } else {
            towers.push_back(x);
        }
    }

    std::cout << towers.size() << "\n";
    return 0;
}