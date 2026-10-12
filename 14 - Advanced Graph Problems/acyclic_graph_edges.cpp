#include <iostream>
#include <vector>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    [[maybe_unused]]
    std::size_t n;

    std::size_t m, a, b;

    std::cin >> n >> m;

    while (m--) {
        std::cin >> a >> b;
        std::cout << (a < b ? a : b) << " " << (a < b ? b : a) << "\n";
    }

    return 0;
}