#include <iostream>
#include <vector>
#include <bit>

constexpr std::size_t MAXN = 2e5 + 5;

constexpr std::size_t log_floor(std::size_t i) {
    return std::bit_width(i) - 1;
}

constexpr std::size_t K = log_floor(MAXN);

std::size_t sparse_table[K + 1][MAXN];

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    std::vector<std::size_t> arr;
    std::size_t n, q, a, b, lg;
    
    std::cin >> n >> q;

    arr.resize(n);
    for (auto& x : arr) {
        std::cin >> x;
    }

    std::copy(arr.begin(), arr.end(), sparse_table[0]);

    for (std::size_t i = 1; i <= K; ++i) {
        for (std::size_t j = 0; j + (1 << i) <= n; ++j) {
            sparse_table[i][j] = std::min(sparse_table[i - 1][j], sparse_table[i - 1][j + (1 << (i - 1))]);
        }
    }

    while (q--) {
        std::cin >> a >> b;
        --a; --b;

        lg = log_floor(b - a + 1);
        std::cout << std::min(sparse_table[lg][a], sparse_table[lg][b - (1 << lg) + 1]) << "\n";
    }

    return 0;
}