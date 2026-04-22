#include <iostream>
#include <vector>
#include <array>

constexpr std::size_t MAXN = 2e5 + 5;
constexpr std::size_t MAXLOGK = 31; // log2 1e9

std::array<std::array<std::size_t, MAXLOGK>, MAXN> next;

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::size_t n, q, x, k;

    std::cin >> n >> q;

    for (std::size_t i = 1; i <= n; ++i) {
        std::cin >> next[i][0];
    }

    for (std::size_t p = 1; p < MAXLOGK; ++p) {
        for (std::size_t v = 1; v <= n; ++v) {
            next[v][p] = next[next[v][p - 1]][p - 1];
        }
    }

    while (q--) {
        std::cin >> x >> k;

        for (std::size_t p = MAXLOGK - 1; p < MAXLOGK; --p) {
            if (k & (1ull << p)) {
                x = next[x][p];
            }
        }

        std::cout << x << "\n";
    }

    return 0;
}