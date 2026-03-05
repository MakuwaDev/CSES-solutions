#include <iostream>
#include <vector>
#include <cstdint>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::vector<int64_t> x;

    std::size_t n;
    int64_t curr, res;
    std::cin >> n;

    x.resize(n);
    for (auto it = x.begin(); it != x.end(); ++it) {
        std::cin >> *it;
    }

    curr = res = x[0];
    for (std::size_t i = 1; i < n; ++i) {
        curr = std::max(curr + x[i], x[i]);
        res = std::max(curr, res);
    }

    std::cout << res << "\n";
    return 0;
}