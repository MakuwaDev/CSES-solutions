#include <iostream>
#include <cstdint>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    uint32_t n;
    std::cin >> n;

    if (n == 1) {
        std::cout <<"1\n";
        return 0;
    } else if (n <= 3) {
        std::cout << "NO SOLUTION\n";
        return 0;
    } else if (n == 4) {
        std::cout << "2 4 1 3\n";
        return 0;
    }

    for (uint32_t i = 1; i <= n; i += 2) {
        std::cout << i << " ";
    }

    for (uint32_t i = 2; i <= n; i += 2) {
        std::cout << i << " ";
    }

    std::cout <<"\n";
    return 0;
}