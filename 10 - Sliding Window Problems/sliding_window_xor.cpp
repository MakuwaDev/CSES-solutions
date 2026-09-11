#include <iostream>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::size_t n, k, x, a, b, c, curr = 0, res = 0, y;

    std::cin >> n >> k;
    std::cin >> x >> a >> b >> c;

    y = x;

    for (std::size_t i = 1; i <= n; ++i) {
        curr ^= x;

        if (i > k) {
            curr ^= y;
            y = (a * y + b) % c;
        }

        if (i >= k) {
            res ^= curr;
        }

        x = (a * x + b) % c;
    }

    std::cout << res << "\n";
    return 0;
}