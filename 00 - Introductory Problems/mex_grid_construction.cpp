#include <iostream>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::size_t n;
    std::cin >> n;

    for (std::size_t r = 0; r < n; ++r) {
        for (std::size_t c = 0; c < n; ++c) {
            std::cout << (r ^ c) << " ";
        }

        std::cout << "\n";
    }

    return 0;
}