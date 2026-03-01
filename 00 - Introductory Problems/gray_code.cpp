#include <iostream>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    for(int i = 0; i < 1 << n; ++i) {
        int gray = i ^ (i >> 1);

        for (int bit = n - 1; bit >= 0; --bit) {
            std::cout << ((gray >> bit) & 1);
        }

        std::cout << "\n";
    }

    return 0;
}