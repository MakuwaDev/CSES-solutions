#include <iostream>
#include <cstdint>
#include <set>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::multiset<uint32_t> tickets;

    std::size_t n, m, x;
    std::cin >> n >> m;

    for (std::size_t i = 0; i < n; ++i) {
        std::cin >> x;
        tickets.insert(x);
    }

    for (std::size_t i = 0; i < m; ++i) {
        std::cin >> x;

        auto it = tickets.upper_bound(x);
        if (it != tickets.begin()) {
            --it;
            std::cout << *it << "\n";
            tickets.erase(it);
        } else {
            std::cout << "-1\n";
        }
    }
}