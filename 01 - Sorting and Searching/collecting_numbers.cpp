#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::vector<std::size_t> ind;

    std::size_t n, res = 0, curr, x;
    std::cin >> n;

    ind.resize(n + 1);
    for (std::size_t i = 0; i < n; ++i) {
        std::cin >> x;
        ind[x] = i;
    }

    curr = n + 1;
    for (std::size_t i = 1; i <= n; ++i) {
        if (ind[i] < curr) {
            ++res;
        }

        curr = ind[i];
    }

    std::cout << res << "\n";
    return 0;
}