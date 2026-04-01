#include <iostream>
#include <vector>

inline std::size_t calculate_k(std::size_t n) {
    std::size_t k = 1, power = 1;

    while (power < n) {
        power <<= 1;
        ++k;
    }

    return k;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::vector<std::vector<std::size_t>> ancestor;
    std::size_t n, q, k, x, y;

    std::cin >> n >> q;

    ancestor.resize(n);

    k = calculate_k(n) + 1;
    for (auto& v : ancestor) {
        v.resize(k);
    }

    ancestor[0][0] = 0;

    for (std::size_t i = 1; i < n; ++i) {
        std::cin >> ancestor[i][0];
        --ancestor[i][0];
    }

    for (std::size_t l = 1; l < k; ++l) {
        for (std::size_t i = 0; i < n; ++i) {
            ancestor[i][l] = ancestor[ancestor[i][l - 1]][l - 1];
        }
    }

    // for (std::size_t i = 0; i < n; ++i) {
    //     std::cout << i << ": ";
    //     for (auto x : ancestor[i]) {
    //         std::cout << x << " ";
    //     }

    //     std::cout << "\n";
    // }

    while (q--) {
        std::cin >> x >> y;
        --x; --y;

        for (std::size_t l = k; l <= k; --l) {
            if ((1ull << l) <= y) {
                y -= (1 << l);
                x = ancestor[x][l];
            }
        }

        if (x == 0) {
            std::cout << "-1\n";
        } else {
            std::cout << ancestor[x][0] + 1 << "\n";
        }
    }

    return 0;
}