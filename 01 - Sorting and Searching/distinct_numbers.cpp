#include <iostream>
#include <set>
#include <cstdint>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::set<uint32_t> s;

    uint32_t n, x;
    std::cin >> n;

    while (n--) {
        std::cin >> x;
        s.insert(x);
    }

    std::cout << s.size() << "\n";
}