#include <iostream>
#include <vector>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::vector<std::string> forest;
    std::vector<std::vector<std::size_t>> psum;
    std::size_t n, q, x1, y1, x2, y2;

    std::cin >> n >> q;

    forest.resize(n);
    psum.resize(n + 1);
    psum[n].resize(n + 1);

    for (std::size_t i = 0; i < n; ++i) {
        std::cin >> forest[i];
        psum[i].resize(n + 1);
    }

    for (std::size_t i = 1; i <= n; ++i) {
        for (std::size_t j = 1; j <= n; ++j) {
            psum[i][j] = psum[i - 1][j] + psum[i][j - 1] + (forest[i - 1][j - 1] == '*') - psum[i - 1][j - 1];
        }
    }

    while (q--) {
        std::cin >> y1 >> x1 >> y2 >> x2;
        std::cout << psum[y2][x2] - psum[y1 - 1][x2] - psum[y2][x1 - 1] + psum[y1 - 1][x1 - 1] << "\n";
    }

    return 0;
}