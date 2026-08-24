#include <iostream>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::size_t t, n, x, nim;

    std::cin >> t;

    while (t--) {
        std::cin >> n;
        
        nim = 0;

        while (n--) {
            std::cin >> x;
            nim ^= x;
        }

        std::cout << (nim == 0 ? "second" : "first") << "\n";
    }

    return 0;
}