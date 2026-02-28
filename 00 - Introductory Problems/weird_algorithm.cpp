#include <iostream>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int x;
    std::cin >> x;

    while (x != 1) {
        std::cout << x << " ";

        if (x & 1) {
            x = 3 * x + 1;
        } else {
            x /= 2;
        }
    }

    std::cout << "1\n";
}
