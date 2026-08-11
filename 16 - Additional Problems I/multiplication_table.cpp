#include <iostream>

std::size_t table_less_equal(std::size_t x, std::size_t n) {
    std::size_t res = 0;

    for (std::size_t i = 1; i <= n; ++i) {
        res += std::min(n, x / i);
    }

    return res;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::size_t n, l, r, m;
    
    std::cin >> n;

    if (n == 1) {
        std::cout << "1\n";
        return 0;
    }

    l = 1;
    r = n * n + 1;

    while (l + 1 < r) {
        m = (l + r) / 2;

        if (table_less_equal(m, n) >= n * n / 2 + 1) {
            r = m;
        } else {
            l = m;
        }
    }

    std::cout << r << "\n";
}