#include <iostream>
#include <vector>
#include <cmath>

constexpr std::size_t MOD = 1e9 + 7;

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::vector<std::vector<std::size_t>> sim;
    std::vector<std::size_t> tmp;
    std::size_t n, k, j, r = 0, c = 0, root;

    std::cin >> n >> k;
    root = std::sqrt(n);


    for (std::size_t i = 1; i <= n; ++i) {
        if (tmp.size() > root) {
            sim.push_back(tmp);
            tmp.clear();
        }

        tmp.push_back(i);
    }

    if (!tmp.empty()) {
        sim.push_back(tmp);
    }

    for (std::size_t i = 0; i < n; ++i) {
        j = k % (n - i);

        while (j) {
            if (c + j < sim[r].size()) {
                c += j;
                j = 0;
            } else {
                j -= sim[r].size() - c;
                c = 0;
                ++r;
            }

            if (r >= sim.size()) {
                r = 0;
            }
        }

        while (sim[r].size() <= c) {
            c = 0;
            ++r;

            if (r >= sim.size()) {
                r = 0;
            }
        }

        std::cout << sim[r][c] << " ";

        if (i != n - 1) {
            sim[r].erase(sim[r].begin() + c);

            while (sim[r].size() <= c) {
                c = 0;
                ++r;

                if (r >= sim.size()) {
                    r = 0;
                }
            }
        }
    }

    std::cout << "\n";
    return 0;
}